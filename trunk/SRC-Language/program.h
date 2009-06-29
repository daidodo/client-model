#ifndef DOZERG_PROGRAM_H_20081114
#define DOZERG_PROGRAM_H_20081114

#include "symbols.h"

struct CProgram
{
    //vars and stmts
    std::vector<std::string> qstr_table;
    __VarTable var_table;
    std::vector<CSharedPtr<CStmt> > global_stmts;
    //commands
    CSharedPtr<CCmd> cur_cmd;
    std::map<std::string,CSharedPtr<CCmd> > cmd_table;
    //connection
    bool conn_defined_; //是否已有默认连接
//functions:
    CProgram();
    CSharedPtr<CCmd> & CurCmd(){return cur_cmd;}
    size_t AddQstr(const std::string & qstr);
    const std::string & GetQstr(size_t i) const;

    CSharedPtr<CVariable> GetVar(const std::string & varname);
    CSharedPtr<CVariable> NewVar(const std::string & varname,CSharedPtr<CVariable> old = 0);
    __VarTable & CurVarTable(){return (cur_cmd ? cur_cmd->var_table : var_table);}
    void AddStmt(CSharedPtr<CAssertExp> stmt);
    void AddStmt(CSharedPtr<CDeclare> stmt);
    void AddStmt(CSharedPtr<CFuncCall> stmt);
    void CmdBegin(CSharedPtr<CVariable> var);
    void CmdEnd();
private:
    bool isGlobal() const{return !cur_cmd;}
    std::vector<CSharedPtr<CStmt> > & curStmtList(){return (cur_cmd ? cur_cmd->stmt_list_ : global_stmts);}
    CSharedPtr<CCmd> findCmd(const std::string & name) const;
    static CSharedPtr<CVariable> findVar(const __VarTable & vt,const std::string & name);
};

#endif
