#ifndef DOZERG_SYMBOLS_H_20081111
#define DOZERG_SYMBOLS_H_20081111

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "types.h"
#include "common/SharedPtr.h"
//#include "common/Sockets.h"

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
};

struct CTcp// : public CTcpConnSocket
{
    const int lineno_;
    //functions:
    explicit CTcp(int ln);
    std::string ToString() const{}
    std::string Signature() const;
};

struct CUdp// : public CUdpSocket
{
    const int lineno_;
    //functions:
    explicit CUdp(int ln);
    std::string ToString() const{}
    std::string Signature() const;
};

//struct CValue
//{
//    union{
//        U8  u8_;
//        S8  s8_;
//        U16 u16_;
//        S16 s16_;
//        U32 u32_;
//        S32 s32_;
//        U64 u64_;
//        S64 s64_;
//        size_t strIdx_;
//    };
//    CSharedPtr<CTcp> tcp_;
//    CSharedPtr<CUdp> udp_;
//    //functions:
//    CValue():u64_(0){}
//};

struct CArrayType;

struct CCommand;

struct CVariable
{
    std::string varname_;
    const int lineno_;
    int type_;
    int simple_type_;
    int ref_count_;
    CSharedPtr<CArrayType> array_type_;
    CSharedPtr<CCommand> host_cmd_;
    CSharedPtr<CVariable> shadow_;
    //functions:
    explicit CVariable(int ln);
    std::string ToString() const;
    std::string Signature() const;
    bool IsGlobal() const{return !host_cmd_;}
    bool Is1stDefine() const{return !ref_count_;}
};

struct CFuncCall;

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
};

struct CArrayType
{
    const int lineno_;
    int simple_type_;
    CSharedPtr<CExpr> expr_;
    //functions:
    explicit CArrayType(int ln);
    std::string ToString() const;
    std::string Signature() const;
    bool CheckDefined(int lineno) const;
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
    int op_token;
    int simple_type;
    CSharedPtr<CVariable> var_;
    CSharedPtr<CExpr> expr_;
    //functions:
    explicit CDeclare(int ln);
    std::string ToString() const;
    std::string Signature() const;
    bool IsGlobalOnly() const;
    bool Validate() const;
    bool IsArray() const{return type_ == 1;}
    bool IsVariable() const{return type_ == 2 || type_ == 3;}
    bool IsFixed() const{return type_ == 5 || type_ == 6;}
    bool IsAssert() const{return type_ == 7;}
    bool IsStream() const{return type_ == 8 || type_ == 9;}
    bool CheckDefined(CSharedPtr<CCommand> cur_cmd);
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
};

struct CStmt
{
    const int lineno_;
    int type_;
    CSharedPtr<CAssertExp> assert_;
    CSharedPtr<CDeclare> declare_;
    CSharedPtr<CFuncCall> func_call_;
    CSharedPtr<CCommand> cmd_;
    //functions:
    explicit CStmt(int ln);
    std::string ToString() const;
    std::string Signature() const;
};

typedef std::map<std::string,CSharedPtr<CVariable> >   __VarTable;

struct CCommand
{
    const int lineno_;
    std::string cmd_name_;
    __VarTable var_table;
    std::vector<CSharedPtr<CStmt> > stmt_list_;
    //functions:
    explicit CCommand(int ln);
    std::string ToString() const;
    std::string Signature() const;
};

#endif
