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
#include "common/SharedPtr.h"
#include "common/Sockets.h"

struct CValue;
struct CFixValue;
struct CTcp;
struct CUdp;
struct CVariable;
struct CExpr;
struct CArgList;
struct CArrayType;
struct CAssertExp;
struct CDeclare;
struct CFuncCall;
struct CStmt;
struct CCmd;

struct CValue
{
    int type_;
    union{
        int int_;       //1
        long long_;     //2
        U8  u8_;        //3
        S8  s8_;        //4
        U16 u16_;       //5
        S16 s16_;       //6
        U32 u32_;       //7
        S32 s32_;       //8
        U64 u64_;       //9
        S64 s64_;       //10
    };
    std::string str_;   //11
    CSharedPtr<CTcp> tcp_;  //12
    CSharedPtr<CUdp> udp_;  //13
    //functions:
    CValue();
    std::string ToString() const;
    std::string Signature() const;
 };

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
    bool Validate() const{return true;}
    int RetType() const;
    CSharedPtr<CValue> Evaluate(int lineno) const;
};

struct CTcp : public CTcpConnSocket
{
    const int lineno_;
    //functions:
    //explicit CTcp(int ln);
    //std::string Signature() const;
};

struct CUdp : public CUdpSocket
{
    const int lineno_;
    //functions:
    //explicit CUdp(int ln);
    //std::string Signature() const;
};

struct CVariable
{
    std::string varname_;
    const int lineno_;
    int type_;
    int tp_token_;
    int ref_count_;
    CSharedPtr<CArrayType> array_type_;
    CSharedPtr<CCmd> host_cmd_;
    CSharedPtr<CVariable> shadow_;
    //functions:
    explicit CVariable(int ln);
    std::string ToString() const;
    std::string Signature() const;
    bool IsGlobal() const{return !host_cmd_;}
    bool Is1stDefine() const{return !ref_count_;}
    bool IsArray() const{return type_ == 2;}
    bool Validate() const{return true;}
    bool IsConnection() const;
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
};

struct CDeclare
{
    const int lineno_;
    int type_;
    int is_def_;
    int op_token_;
    int tp_token_;
    CSharedPtr<CVariable> var_;
    CSharedPtr<CExpr> expr_;
    double eva_priority_;
    CSharedPtr<CValue> val_;
    //functions:
    explicit CDeclare(int ln);
    std::string ToString() const;
    std::string Signature() const;
    bool IsGlobalOnly() const;
    bool Validate() const;
    bool IsArray() const{return type_ == 1;}
    bool IsPost() const{return !IsFixed();}
    bool IsFixed() const{return type_ == 5 || type_ == 6;}
    bool IsAssert() const{return type_ == 7;}
    bool IsStream() const{return type_ == 8 || type_ == 9;}
    bool IsConnection() const{return var_->IsConnection();}
    bool CheckDefined(CSharedPtr<CCmd> cur_cmd);
    std::string Depend() const{return (expr_ ? expr_->Depend() : "");}
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
    bool HasSideEffect() const{return RetType() == 0;}
    CSharedPtr<CValue> Evaluate() const;
    std::string Depend() const;
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
    std::string cmd_name_;
    __VarTable var_table;
    std::vector<CSharedPtr<CStmt> > stmt_list_;
    //functions:
    explicit CCmd(int ln);
    std::string ToString() const;
    std::string Signature() const;
};

#endif
