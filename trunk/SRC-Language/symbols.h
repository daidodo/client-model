#ifndef DOZERG_SYMBOLS_H_20081111
#define DOZERG_SYMBOLS_H_20081111

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "types.h"
#include "common/Sockets.h"

struct CFixValue
{
    const int lineno_;
    int type_;
    int number_;
    size_t strIdx_;
    //functions:
    explicit CFixValue(int ln);
    std::string ToString() const;
    std::string Signature() const;
};

struct CTcp : public CTcpConnSocket
{
    const int lineno_;
    //functions:
    explicit CTcp(int ln);
    std::string Signature() const;
};

struct CUdp : public CUdpSocket
{
    const int lineno_;
    //functions:
    explicit CUdp(int ln);
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
    std::vector<CValue> val_;
    //functions:
    explicit CVariable(int ln);
    ~CVariable();
    std::string ToString() const;
    std::string Signature() const;
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

struct CProgram
{
    //vars and stmts
    std::vector<std::string> qstr_table;
    __VarTable var_table;
    std::vector<CStmt *> global_stmts;
    //connections
    bool tcp_default;
    std::vector<CTcp *> tcp_table;
    std::vector<CUdp *> udp_table;
    //commands
    CCommand * cur_cmd;
    std::map<std::string,CCommand *> cmd_table;
//functions:
    CProgram();
    ~CProgram();
    bool isGlobal() const{return !cur_cmd;}
    size_t AddQstr(const std::string qstr);
    static CVariable * findVar(const __VarTable & vt,const std::string & name);
    CVariable * GetVar(const std::string & varname);
    CVariable * NewVar(const std::string & varname,CVariable * old = 0);
    const std::string & GetQstr(size_t i) const;
    void AddStmt(CAssertExp * stmt);
    void AddStmt(CDeclare * stmt);
    void AddStmt(CFuncCall * stmt);
    void CmdBegin(CVariable * var_name);
    void CmdEnd();
};

#endif
