#ifndef DOZERG_SYMBOLS_H_20081111
#define DOZERG_SYMBOLS_H_20081111

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>
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
struct CCmd;

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
    bool CheckDefined(int lineno) const;
    int RetType() const;
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
    double eva_priority_;
    //value
    CSharedPtr<CValue> val_;
    ssize_t offset_;    //for post evaluation
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
    bool IsRecvOnly() const{return IsArray() || IsAssert() || IsStreamIn();}
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

struct CCmd
{
    const int lineno_;
    int send_flag_; //0:unknown ; 1:send ; 2:recv
    std::string cmd_name_;
    __VarTable var_table;
    std::vector<CSharedPtr<CStmt> > stmt_list_;
    std::vector<CSharedPtr<CValue> > conn_list_;
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
    size_t SendDataOffset() const{return outds_.Size();}
    //send cmd
    bool SendValue(CSharedPtr<CValue> v);
    //recv cmd
    void RecvValue(CSharedPtr<CValue> v);
    void RecvArray(CSharedPtr<CDeclare> d){}
    void RecvAssert(CSharedPtr<CDeclare> d){}
    void RecvStreamIn(CSharedPtr<CDeclare> d){}
};

#endif
