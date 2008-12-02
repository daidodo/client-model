#ifndef DOZERG_SYMBOLS_H_20081111
#define DOZERG_SYMBOLS_H_20081111

#include <map>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>
#include "config.h"
#include "types.h"
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
struct CCmdStruct;

struct CFixValue
{
    const int lineno_;
    int type_;
    int int_;
    long long_;
    long long i64_;
    size_t strIdx_;
    //functions:
    explicit CFixValue(int ln);
    std::string ToString() const;
    std::string Signature() const;
    int RetType() const;
    CSharedPtr<CValue> Evaluate(int lineno) const;
};

struct CVariable
{
    std::string varname_;
    const int lineno_;
    int type_;  //0:unknown ; 1:simple ; 2:array ; 3:struct
    int tp_token_;
    int ref_count_;
    ssize_t begin_;     //for BEGIN(var), END(var)
    CSharedPtr<CArrayType> array_type_;
    CSharedPtr<CVariable> struct_name_;
    CSharedPtr<CCmdStruct> struct_type_;
    CSharedPtr<CCmdStruct> host_cmd_;
    CSharedPtr<CVariable> shadow_;
    //functions:
    explicit CVariable(int ln);
    std::string ToString() const;
    std::string Signature() const;
    bool IsGlobal() const{return !host_cmd_;}
    bool Is1stDefine() const{return ref_count_ == 0;}
    bool IsArray() const{return type_ == 2;}
    bool IsStruct() const{return type_ == 3;}
    bool IsConnection() const;
    bool IsRaw() const;
    int RetType() const;
    CSharedPtr<CValue> Evaluate(int lineno) const;
    CSharedPtr<CValue> Initial(int lineno) const;
    CSharedPtr<CVariable> Copy() const;
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
    CSharedPtr<CExpr> Copy() const;
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
    CSharedPtr<CArgList> Copy() const;
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
    CSharedPtr<CArrayType> Copy() const;
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
    CSharedPtr<CAssertExp> Copy() const;
};

struct CDeclare
{
    const int lineno_;
    int type_;
    int is_def_;
    int op_token_;
    double eva_priority_;
    CSharedPtr<CVariable> var_;
    CSharedPtr<CExpr> expr_;
    //value
    CSharedPtr<CValue> val_;
    ssize_t offset_;    //for post evaluation
    //functions:
    explicit CDeclare(int ln);
    std::string ToString() const;
    std::string Signature() const;
    bool IsGlobalOnly() const;
    bool Validate() const;
    bool IsStruct() const{return var_->IsStruct();}
    bool IsArray() const{return type_ == 1;}
    bool IsSimplePost() const{return type_ == 2 || type_ == 3 || type_ == 4;}
    bool IsFixed() const{return type_ == 5 || type_ == 6;}
    bool IsPost() const{return IsSimplePost() || IsStreamOut();}
    bool IsAssert() const{return type_ == 7;}
    bool IsStream() const{return type_ == 8 || type_ == 9;}
    bool IsStreamIn() const;
    bool IsStreamOut() const;
    bool IsConnection() const{return var_->IsConnection();}
    bool IsLocalOnly() const{return IsArray() || IsAssert() || IsStream() || IsStruct();}
    bool IsRecvOnly() const{return IsArray() || IsAssert() || IsStreamIn();}
    bool IsSendOnly() const{return IsFixed() || IsStreamOut();}
    bool CheckDefined(CSharedPtr<CCmdStruct> cur_cmd);
    std::string Depend() const{return (expr_ ? expr_->Depend() : "");}
    void FixRaw();
    CSharedPtr<CValue> Evaluate();
    CSharedPtr<CDeclare> Copy() const;
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
    int IsSendRecv() const; //0:false ; 1:send ; 2:recv
    CSharedPtr<CValue> Evaluate() const;
    void Invoke(CSharedPtr<CCmdStruct> cmd) const;
    CSharedPtr<CFuncCall> Copy() const;
};

struct CStmt
{
    const int lineno_;
    int type_;
    CSharedPtr<CAssertExp> assert_;
    CSharedPtr<CDeclare> declare_;
    CSharedPtr<CFuncCall> func_call_;
    CSharedPtr<CCmdStruct> cmd_struct_;
    //functions:
    explicit CStmt(int ln);
    std::string ToString() const;
    std::string Signature() const;
    CSharedPtr<CStmt> Copy() const;
};

typedef std::map<std::string,CSharedPtr<CVariable> >   __VarTable;

struct CCmdStruct
{
    const int lineno_;
    int endlineno_;
    int cmd_send_flag_; //0:cmd ; 1:send cmd ; 2:recv cmd ; 3:struct
    std::string struct_name_;
    __VarTable var_table;
    std::vector<CSharedPtr<CStmt> > stmt_list_;
    //cmd
    std::vector<CSharedPtr<CValue> > conn_list_;
    CSharedPtr<CArgList> begin_list_;    //BEGIN的变量名堆栈
    //send cmd
    COutByteStream outds_;
    //recv cmd
    std::vector<char> recv_data_;
    CInByteStream inds_;
    //functions:
    explicit CCmdStruct(int ln);
    std::string ToString() const;
    std::string Signature() const;
    bool IsSend() const{return cmd_send_flag_ == 1;}
    bool IsRecv() const{return cmd_send_flag_ == 2;}
    bool IsStruct() const{return cmd_send_flag_ == 3;}
    bool IsCmd() const{return !IsStruct();}
    CSharedPtr<CCmdStruct> StructCopy() const;
    //cmd
    void SetByteOrder(bool net_bo);
    void AddConnection(CSharedPtr<CValue> conn,int lineno);
    //send cmd
    size_t SendDataOffset() const{return outds_.Size();}
    bool PutValue(CSharedPtr<CValue> v);
    bool PostPutValue(CSharedPtr<CValue> v,size_t offset);
    bool PostInsertValue(CSharedPtr<CValue> v,size_t offset);
    void Begin(CSharedPtr<CExpr> v);
    void End(CSharedPtr<CExpr> v);
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
    //both
    void InvokeFun(bool (*fp)(std::vector<char> &,std::vector<char> &),size_t sz,int lineno,const std::string & fname);
};

#endif
