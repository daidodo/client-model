#ifndef DOZERG_SYMBOLS_H_20081111
#define DOZERG_SYMBOLS_H_20081111

#include "platform.h"
#include <map>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>
#include "config.h"
#include "errors.h"
#include "rt_structs.h"
#include "common/SharedPtr.h"
#include "common/DataStream.h"

struct CFixValue;
struct CVariable;
struct CExpr;
struct CArgList;
struct CArrayType;
struct CAssertExp;
struct CDeclare;
struct CFuncCall;
struct CStmt;
struct CCmd;

struct CFixValue
{
    const int lineno_;
    int type_;
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
    std::string Signature() const;
    int RetType() const{return type_;}
    CSharedPtr<CValue> Evaluate(int lineno) const;
};

struct CVariable
{
    std::string varname_;
    const int lineno_;
    int type_;
    int tp_token_;
    int ref_count_;
    ssize_t begin_;     //for BEGIN(var), END(var)
    CSharedPtr<CArrayType> array_type_;
    CSharedPtr<CCmd> host_cmd_;
    CSharedPtr<CVariable> shadow_;
    //functions:
    explicit CVariable(int ln);
    std::string ToString() const;
    std::string Signature() const;
    bool IsGlobal() const{return !host_cmd_;}
    bool Is1stDefine() const{return ref_count_ == 0;}
    bool IsArray() const{return type_ == 2;}
    bool IsConnection() const;
    bool IsRaw() const;
    int RetType() const;
    CSharedPtr<CValue> Evaluate(int lineno) const;
    CSharedPtr<CValue> Initial(int lineno) const;
};

struct CExpr
{
    const int lineno_;
    int type_;
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

struct CArgList
{
    const int lineno_;
    std::vector<CSharedPtr<CExpr> > args_;
    //fuctions:
    explicit CArgList(int ln);
    CSharedPtr<CExpr> operator [](size_t i) const;
    void Add(CSharedPtr<CExpr> arg);
    void Erase(CSharedPtr<CExpr> arg);
    std::string ToString() const;
    std::string Signature() const;
    bool CheckDefined(int lineno) const;
    bool Validate() const;
    void RetType(std::vector<int> & ret) const;
    bool Evaluate(std::vector<CSharedPtr<CValue> > & ret,int lineno) const;
    std::string Depend() const;
};

struct CArrayType
{
    const int lineno_;
    int tp_token_;
    int sz_;     //数组大小
    CSharedPtr<CExpr> expr_;
    //functions:
    explicit CArrayType(int ln);
    std::string ToString() const;
    std::string Signature() const;
    bool Validate() const;
    bool CheckDefined(int lineno) const;
    int RetType() const;
    bool HasSize() const{return sz_ > 0;}
    int Size() const{return sz_;}
    CSharedPtr<CValue> Evaluate() const;
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

struct CDeclare
{
    const int lineno_;
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
    //functions:
    explicit CDeclare(int ln);
    std::string ToString() const;
    std::string Signature() const;
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
    int IsSendRecv() const; //0:false ; 1:send ; 2:recv
    CSharedPtr<CValue> Evaluate() const;
    void Invoke(CSharedPtr<CCmd> cmd) const;
};

struct CStmt
{
    const int lineno_;
    int type_;
    CSharedPtr<CAssertExp> assert_;
    CSharedPtr<CDeclare> declare_;
    CSharedPtr<CFuncCall> func_call_;
    CSharedPtr<CCmd> cmd_;
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
    const int lineno_;
    int endlineno_;
    int send_flag_; //0:unknown ; 1:send ; 2:recv
    std::string cmd_name_;
    __VarTable var_table;
    size_t cur_stmt_index_;
    std::vector<CSharedPtr<CStmt> > stmt_list_;
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
    //functions:
    explicit CCmd(int ln);
    std::string ToString() const;
    std::string Signature() const;
    bool IsSend() const{return send_flag_ == 1;}
    bool IsRecv() const{return send_flag_ == 2;}
    void SetByteOrder(bool net_bo);
    void AddConnection(CSharedPtr<CValue> conn,int lineno);
    void InvokeFun(bool (*fp)(std::vector<char> &,std::vector<char> &),size_t sz,int lineno,const std::string & fname);
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
