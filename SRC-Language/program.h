#ifndef DOZERG_PROGRAM_H_20081114
#define DOZERG_PROGRAM_H_20081114

#include "symbols.h"

class CProgram
{
    template<class T>
    struct __Del{
        T * p_;
        explicit __Del(T *& p):p_(p){}
        ~__Del();
        void Succ(){p_ = 0;}
    };
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
    std::vector<CCommand *> cmd_vec;
//functions:
    static CVariable * findVar(const __VarTable & vt,const std::string & name);
public:
    CProgram();
    ~CProgram();
    CCommand * CurCmd(){return cur_cmd;}
    bool isGlobal() const{return !cur_cmd;}
    size_t AddQstr(const std::string qstr);
    CVariable * GetVar(const std::string & varname);
    CVariable * NewVar(const std::string & varname,CVariable * old = 0);
    const std::string & GetQstr(size_t i) const;
    void AddStmt(CAssertExp * stmt);
    void AddStmt(CDeclare * stmt);
    void AddStmt(CFuncCall * stmt);
    void CmdBegin(CVariable * var_name);
    void CmdEnd();
private:
    CCommand * findCmd(const std::string & name) const;
    __VarTable & curVarTable(){return (cur_cmd ? cur_cmd->var_table : var_table);}
};

#endif
