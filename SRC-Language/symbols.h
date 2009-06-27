#ifndef DOZERG_SYMBOLS_H_20081111
#define DOZERG_SYMBOLS_H_20081111

#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include "config.h"
#include "errors.h"
#include "rt_structs.h"
#include "SRC_language.h"

struct CFixValue;
struct CArrayValue;
struct CExpr;
struct CVariable;
struct CArgList;
struct CConstDecl;
struct CPostDecl;
struct CArrayDecl;
struct CAssertDecl;
struct CStreamDecl;
struct CDefineDecl;
struct CDeclare;
struct CFuncCall;
struct CAssertExp;
struct CStmt;
struct CCmd;

struct CFixValue
{
    const int lineno_;
    int flag_;      //DT_XXX
    union{
        int int_;
        long long_;
        long long i64_;
        size_t strIdx_;
        int prog_arg_;
    };
    //functions:
    explicit CFixValue(int ln);
    std::string ToString() const;
    std::string Signature() const{return ToString();}
    int RetType() const{return type_;}

    CSharedPtr<CValue> Evaluate(int lineno) const;
};

struct CArrayValue
{
    const int lineno_;
    size_t strIdx_;
    CSharedPtr<CArgList> arglist_;
    //functions:
    explicit CArrayValue(int ln);
    std::string ToString() const;
    std::string Signature() const;

};

struct CExpr
{
    const int lineno_;
    CSharedPtr<CFixValue> fix_value_;
    CSharedPtr<CFuncCall> func_call_;
    CSharedPtr<CVariable> var_;
    //functions:
    explicit CExpr(int ln);
    std::string ToString() const;
    std::string Signature() const;

    bool IsVar() const{return type_ == 3;}
    bool CheckDefined(int lineno) const;
    bool Validate() const;
    int RetType() const;
    CSharedPtr<CValue> Evaluate() const;
    std::string Depend() const;
};

struct CVariable
{
    const int lineno_;
    int flag_;      //TF_XXX
    int tp_token_;
    CSharedPtr<CExpr> sz_expr_; //size expression for array type
    std::string varname_;
    //internel
    int ref_count_;         //记录是否有重复定义
    CSharedPtr<CCmd> host_cmd_;
    CSharedPtr<CVariable> shadow_;  //当出现重复定义时，记录前一个定义
    //functions:
    static CSharedPtr<CVariable> CheckRedefine(CSharedPtr<CVariable> var,int lineno,CSharedPtr<CCmd> cur_cmd);
    explicit CVariable(int ln);
    std::string ToString() const;
    std::string Signature() const;

    bool IsGlobal() const{return !host_cmd_;}
    bool Is1stDefine() const{return ref_count_ == 0;}
    bool IsArray() const{return datatype_ != 0;}
    bool IsConnection() const;
    bool IsRaw() const;
    int RetType() const;
    CSharedPtr<CValue> Evaluate(int lineno) const;
    CSharedPtr<CValue> Initial(int lineno) const;
};

struct CArgList
{
    const int lineno_;
    std::list<CSharedPtr<CExpr> > args_;
    //fuctions:
    explicit CArgList(int ln);
    std::string ToString() const;
    std::string Signature() const;
    void Add(CSharedPtr<CExpr> arg);

    CSharedPtr<CExpr> operator [](size_t i) const;
    void Erase(CSharedPtr<CExpr> arg);
    bool CheckDefined(int lineno) const;
    bool Validate() const;
    void RetType(std::vector<int> & ret) const;
    bool Evaluate(std::vector<CSharedPtr<CValue> > & ret,int lineno) const;
    std::string Depend() const;
};

struct CConstDecl
{
    const int lineno_;
    CSharedPtr<CVariable> var_;
    CSharedPtr<CExpr> expr_;
    //functions:
    explicit CConstDecl(int ln);
    std::string ToString() const;
    std::string Signature() const;
    void AddArg(CSharedPtr<CArgList> arg_list,int lineno){
        assert(var_);
        assert(!expr_);
        if(arg_list){
            expr_ = New<CExpr>(lineno);
            expr_->func_call_ =  New<CFuncCall>(lineno);
            expr_->func_call_->ft_token_ = var_->tp_token_;
            expr_->func_call_->arg_list_ = arg_list;
        }
    }
};

struct CPostDecl
{
    const int lineno_;
    CSharedPtr<CVariable> var_;
    CSharedPtr<CExpr> expr_;
    //functions:
    explicit CPostDecl(int ln);
    std::string ToString() const;
    std::string Signature() const;
    void AddArg(CSharedPtr<CArgList> arg_list,int lineno){
        if(arg_list){
            expr_ = New<CExpr>(lineno);
            expr_->func_call_ =  New<CFuncCall>(lineno);
            expr_->func_call_->ft_token_ = var_->tp_token_;
            expr_->func_call_->arg_list_ = arg_list;
        }
    }
};

struct CArrayDecl
{
    const int lineno_;
    CSharedPtr<CVariable> var_;
    CSharedPtr<CArrayValue> arr_val_;
    //functions:
    explicit CArrayDecl(int ln);
    std::string ToString() const;
    std::string Signature() const;
};

struct CAssertDecl
{
    const int lineno_;
    CSharedPtr<CVariable> var_;
    int comp_op_;
    CSharedPtr<CExpr> expr_;
    //functions:
    explicit CAssertDecl(int ln);
    std::string ToString() const;
    std::string Signature() const;
};

struct CStreamDecl
{
    const int lineno_;
    CSharedPtr<CVariable> var_;
    int stream_op_;
    CSharedPtr<CExpr> expr_;
    int tp_token_;
    //functions:
    explicit CStreamDecl(int ln);
    std::string ToString() const;
    std::string Signature() const;
};

struct CDefineDecl
{
    const int lineno_;
    CSharedPtr<CConstDecl> const_decl_;
    CSharedPtr<CPostDecl> post_decl_;
    //functions:
    explicit CDefineDecl(int ln);
    std::string ToString() const;
    std::string Signature() const;
};

struct CDeclare
{
    const int lineno_;
    CSharedPtr<CConstDecl>  constDecl_;
    CSharedPtr<CPostDecl>   postDecl_;
    CSharedPtr<CArrayDecl>  arrayDecl_;
    CSharedPtr<CAssertDecl> assertDecl_;
    CSharedPtr<CStreamDecl> streamDecl_;
    CSharedPtr<CDefineDecl> defDecl_;
    //functions:
    explicit CDeclare(int ln);
    std::string ToString() const;
    std::string Signature() const;


    int type_;
    int is_def_;
    int op_token_;
    CSharedPtr<CVariable> var_;
    CSharedPtr<CExpr> expr_;
    //value
    CSharedPtr<CValue> val_;
    //post evaluation
    double eva_priority_;
    ssize_t offset_;
    bool post_byte_order_;  //延后求值的变量记录字节序：true:NBO ; false:HBO
    bool IsGlobalOnly() const;
    bool Validate() const;
    bool IsArray() const{return type_ == 1;}
    bool IsSimplePost() const{return type_ == 2 || type_ == 3 || type_ == 4;}
    bool IsFixed() const{return type_ == 5 || type_ == 6;}
    bool IsPost() const{return IsSimplePost() || IsStreamOut();}
    bool IsAssert() const{return type_ == 7;}
    bool IsStream() const{return type_ == 8 || type_ == 9;}
    bool IsStreamIn() const;
    bool IsStreamOut() const;
    bool IsConnection() const{return var_->IsConnection();}
    bool IsLocalOnly() const{return IsArray() || IsAssert() || IsStream();}
    bool IsRecvOnly() const{return IsAssert() || IsStreamIn();}
    bool IsSendOnly() const{return IsFixed() || IsStreamOut();}
    bool CheckDefined(CSharedPtr<CCmd> cur_cmd);
    std::string Depend() const{return (expr_ ? expr_->Depend() : "");}
    void FixRaw();
    CSharedPtr<CValue> Evaluate();
};

struct CFuncCall
{
    const int lineno_;
    int ft_token_;
    CSharedPtr<CArgList> arg_list_;
    //functions:
    explicit CFuncCall(int ln);
    std::string ToString() const;
    std::string Signature() const;

    bool CheckDefined() const;
    bool Validate() const;
    bool IsConnection() const;
    bool IsGlobalOnly() const;
    bool IsLocalOnly() const;
    int RetType() const;
    bool HasSideEffect() const{return (RetType() == 0 || IsConnection());}
    std::string Depend() const;
    int IsArrayBeginEnd() const;    //0:false ; 1:begin ; 2:end
    int IsSendRecv() const;         //0:false ; 1:send ; 2:recv
    CSharedPtr<CValue> Evaluate() const;
    void Invoke(CSharedPtr<CCmd> cmd) const;
};

struct CAssertExp
{
    const int lineno_;
    int op_token_;
    CSharedPtr<CExpr> expr1_;
    CSharedPtr<CExpr> expr2_;
    //functions:
    explicit CAssertExp(int ln);
    std::string ToString() const;
    std::string Signature() const;

    bool Validate() const;
    bool CheckDefined() const;
    //return: 0-assert false; 1-assert true; -1-runtime error
    bool Assert() const;
};

struct CStmt
{
    const int lineno_;
    CSharedPtr<CDeclare>    declare_;
    CSharedPtr<CFuncCall>   func_call_;
    CSharedPtr<CAssertExp>  assert_;
    CSharedPtr<CCmd>        cmd_;
    //functions:
    explicit CStmt(int ln);
    std::string ToString() const;
    std::string Signature() const;
};

typedef std::map<std::string,CSharedPtr<CVariable> >   __VarTable;

struct CArrayRange
{
    int lineno_;
    ssize_t start_index_;
    ssize_t end_index_;
    ssize_t cur_;
    ssize_t sz_;
    //functions:
    explicit CArrayRange(int ln = -1);
};

struct CCmd
{
    static const U32 MAX_ARRAY_SIZE = 65535;
    const int lineno_;
    int end_lineno_;
    int send_flag_;     //SF_XXX
    std::string cmd_name_;
    __VarTable var_table;
    std::vector<CSharedPtr<CStmt> > stmt_list_;
    //functions:
    explicit CCmd(int ln);
    std::string ToString() const;
    std::string Signature() const;

    size_t cur_stmt_index_;
    std::vector<CSharedPtr<CValue> > conn_list_;
    CSharedPtr<CArgList> begin_list_;   //BEGIN的变量名堆栈
    size_t array_index_;                //当前数组索引，只在编译的时候使用
    std::vector<size_t> array_stack_;   //数组循环堆栈
    std::vector<CArrayRange> array_range_;
    //send cmd
    COutByteStream outds_;
    //recv cmd
    std::vector<char> recv_data_;
    CInByteStream inds_;

    bool IsSend() const{return send_flag_ == 1;}
    bool IsRecv() const{return send_flag_ == 2;}
    void SetByteOrder(bool net_bo);
    void AddConnection(CSharedPtr<CValue> conn,int lineno);
    void InvokeFun(__SRC_UserFunc fp,unsigned int dst_max_len,size_t sz,int lineno,const std::string & fname);
    void AddArrayBegin(int lineno);
    void AddArrayEnd(int lineno);
    void StartArray(int lineno);
    void StartArray(size_t sz,int lineno);
    void EndArray(int lineno);
    bool IsInArray() const{return !array_stack_.empty();}
    std::string ArrayIndexString() const;
    //send cmd
    size_t SendDataOffset() const{return outds_.Size();}
    bool PutValue(CSharedPtr<CValue> v);
    bool PutArray(CSharedPtr<CDeclare> d);
    bool PostPutValue(CSharedPtr<CValue> v,size_t offset);
    bool PostInsertValue(CSharedPtr<CValue> v,size_t offset);
    void Begin(CSharedPtr<CExpr> v);
    void End(CSharedPtr<CExpr> v);
    bool BeginEmpty() const;
    bool SendData(const std::vector<char> & buf) const;
    //recv cmd
    bool GetValue(CSharedPtr<CValue> v,int lineno);
    template<typename T>
    bool GetVal(T & v,int lineno){
        if(!(inds_>>v)){
#if __REAL_CONNECT
            if(inds_.Status() == 1){
                if(!RecvData(lineno))
                    return false;
                return inds_>>v;
            }
#endif
            return false;
        }
        return true;
    }
    bool GetRaw(std::string & res,const std::string & v,int lineno);
    bool GetArray(CSharedPtr<CDeclare> d);
    bool GetAssert(CSharedPtr<CDeclare> d,CSharedPtr<CValue> v);
    bool GetStreamIn(CSharedPtr<CDeclare> d,CSharedPtr<CValue> v);
    bool RecvData(int lineno);
    void DumpRecvData() const;
    bool EnsureRecvData(size_t sz,int lineno);
};

#endif
