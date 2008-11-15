#ifndef DOZERG_SYMBOLS_H_20081111
#define DOZERG_SYMBOLS_H_20081111

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "types.h"
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

struct CValue
{
    union{
        U8  u8_;
        S8  s8_;
        U16 u16_;
        S16 s16_;
        U32 u32_;
        S32 s32_;
        U64 u64_;
        S64 s64_;
        size_t strIdx_;
        CTcp * tcp_;
        CUdp * udp_;
    };
    //functions:
    CValue():u64_(0){}
};

struct CArrayType;

struct CCommand;

struct CVariable
{
    std::string varname_;
    const int lineno_;
    int type_;
    int simple_type_;
    int ref_count_;
    CArrayType * array_type_;
    CCommand * host_cmd_;
    CVariable * shadow_;
    std::vector<CValue> val_;
    //functions:
    explicit CVariable(int ln);
    ~CVariable();
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
    CFixValue * fix_value_;
    CFuncCall * func_call_;
    CVariable * var_;
    //functions:
    explicit CExpr(int ln);
    ~CExpr();
    std::string ToString() const;
    std::string Signature() const;
    bool CheckDefined(int lineno) const;
    bool IsVar() const{return type_ == 3;}
};

struct CArrayType
{
    const int lineno_;
    int simple_type_;
    CExpr * expr_;
    //functions:
    explicit CArrayType(int ln);
    ~CArrayType();
    std::string ToString() const;
    std::string Signature() const;
    bool CheckDefined(int lineno) const;
};

struct CAssertExp
{
    const int lineno_;
    int op_token_;
    CExpr * expr1_;
    CExpr * expr2_;
    //functions:
    explicit CAssertExp(int ln);
    ~CAssertExp();
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
    CVariable * var_;
    CExpr * expr_;
    //functions:
    explicit CDeclare(int ln);
    ~CDeclare();
    std::string ToString() const;
    std::string Signature() const;
    bool IsGlobalOnly() const;
    bool Validate() const;          //self validation
    bool IsArray() const{return type_ == 1;}
    bool IsVariable() const{return type_ == 2 || type_ == 3;}
    bool IsFixed() const{return type_ == 5 || type_ == 6;}
    bool IsAssert() const{return type_ == 7;}
    bool IsStream() const{return type_ == 8 || type_ == 9;}
    bool CheckDefined(CCommand * cur_cmd);
};

struct CArgList
{
    const int lineno_;
    std::vector<CExpr *> args_;
    //fuctions:
    explicit CArgList(int ln);
    ~CArgList();
    CExpr * operator [](size_t i) const;
    void Add(CExpr * arg);
    std::string ToString() const;
    std::string Signature() const;
    bool CheckDefined(int lineno) const;
};

struct CFuncCall
{
    const int lineno_;
    int ft_token_;
    CArgList * arg_list_;
    //functions:
    explicit CFuncCall(int ln);
    ~CFuncCall();
    std::string ToString() const;
    std::string Signature() const;
    bool CheckDefined() const;
};

struct CStmt
{
    const int lineno_;
    int type_;
    CAssertExp * assert_;
    CDeclare * declare_;
    CFuncCall * func_call_;
    //functions:
    explicit CStmt(int ln);
    ~CStmt();
    std::string ToString() const;
    std::string Signature() const;
};

typedef std::map<std::string,CVariable *>   __VarTable;

struct CCommand
{
    const int lineno_;
    std::string cmd_name_;
    __VarTable var_table;
    std::vector<CStmt *> stmt_list_;
    //functions:
    explicit CCommand(int ln);
    ~CCommand();
    std::string ToString() const;
    std::string Signature() const;
};

#endif
