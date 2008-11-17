#ifndef DOZERG_PROGRAM_H_20081114
#define DOZERG_PROGRAM_H_20081114

#include "symbols.h"

class CProgram
{
    //vars and stmts
    std::vector<std::string> qstr_table;
    __VarTable var_table;
    std::vector<CSharedPtr<CStmt> > global_stmts;
    //connections
    bool tcp_default;
    std::vector<CSharedPtr<CTcp> > tcp_table;
    std::vector<CSharedPtr<CUdp> > udp_table;
    //commands
    CSharedPtr<CCommand> cur_cmd;
    std::map<std::string,CSharedPtr<CCommand> > cmd_table;
//functions:
    static CSharedPtr<CVariable> findVar(const __VarTable & vt,const std::string & name);
public:
    CProgram();
    CSharedPtr<CCommand> & CurCmd(){return cur_cmd;}
    bool isGlobal() const{return !cur_cmd;}
    size_t AddQstr(const std::string qstr);
    CSharedPtr<CVariable> GetVar(const std::string & varname);
    CSharedPtr<CVariable> NewVar(const std::string & varname,CSharedPtr<CVariable> old = 0);
    const std::string & GetQstr(size_t i) const;
    __VarTable & CurVarTable(){return (cur_cmd ? cur_cmd->var_table : var_table);}
    void AddStmt(CSharedPtr<CAssertExp> stmt);
    void AddStmt(CSharedPtr<CDeclare> stmt);
    void AddStmt(CSharedPtr<CFuncCall> stmt);
    void CmdBegin(CSharedPtr<CVariable> var);
    void CmdEnd();
private:
    CSharedPtr<CCommand> findCmd(const std::string & name) const;
    std::vector<CSharedPtr<CStmt> > & curStmtList(){return (cur_cmd ? cur_cmd->stmt_list_ : global_stmts);}
};

#endif
