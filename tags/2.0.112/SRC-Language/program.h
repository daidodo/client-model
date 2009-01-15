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
    CSharedPtr<CCmdStruct> cur_cmd;
    std::map<std::string,CSharedPtr<CCmdStruct> > cmd_table;
    //connection
    bool conn_defined_; //是否已有默认连接
//functions:
    CProgram();
    CSharedPtr<CCmdStruct> & CurCmd(){return cur_cmd;}
    bool isGlobal() const{return !cur_cmd;}
    size_t AddQstr(const std::string qstr);
    CSharedPtr<CVariable> GetVar(const std::string & varname);
    CSharedPtr<CVariable> NewVar(const std::string & varname,CSharedPtr<CVariable> old = 0);
    const std::string & GetQstr(size_t i) const;
    __VarTable & CurVarTable(){return (cur_cmd ? cur_cmd->var_table : var_table);}
    void AddStmt(CSharedPtr<CAssertExp> stmt);
    void AddStmt(CSharedPtr<CDeclare> stmt);
    void AddStmt(CSharedPtr<CFuncCall> stmt);
    void CmdStructBegin(CSharedPtr<CVariable> var,bool is_cmd = true);
    void CmdStructEnd(bool is_cmd = true);
private:
    CSharedPtr<CCmdStruct> findCmdStruct(const std::string & name) const;
    std::vector<CSharedPtr<CStmt> > & curStmtList(){return (cur_cmd ? cur_cmd->stmt_list_ : global_stmts);}
    static CSharedPtr<CVariable> findVar(const __VarTable & vt,const std::string & name);
};

#endif
