#include "dbg.h"
#include "errors.h"
#include "global.h"

CGlobal::CGlobal()
    : lineno(1)
    , tcp_default(true)
    , cur_cmd(0)
{}

CGlobal::~CGlobal()
{
    //vars and stmts
    for(__VarTable::iterator i = var_table.begin();i != var_table.end();++i)
        Delete(i->second);
    std::for_each(global_stmts.begin(),global_stmts.end(),Delete<CStmt>);
    //connections
    std::for_each(tcp_table.begin(),tcp_table.end(),Delete<CTcp>);
    std::for_each(udp_table.begin(),udp_table.end(),Delete<CUdp>);
    //commands
    for(std::map<std::string,CCommand *>::iterator i = cmd_table.begin();i != cmd_table.end();++i)
        Delete(i->second);
}

CVariable * CGlobal::GetVar(const std::string & varname){
    CVariable * ret = 0;
    if(cur_cmd)
        ret = findVar(cur_cmd->var_table,varname);
    if(!ret)
        ret = findVar(var_table,varname);
    if(!ret)
        return NewVar(varname);
    ++ret->ref_count_;
    return ret;
}

CVariable * CGlobal::NewVar(const std::string & varname,CVariable * old)
{
    __VarTable & vt = (isGlobal() ? var_table : cur_cmd->var_table);
    CVariable *& ret = vt[varname];
    assert(!ret);
    ret = New<CVariable>(lineno);
    ret->varname_ = varname;
    ret->host_cmd_ = cur_cmd;
    if(old)
        --old->ref_count_;
    return ret;
}

void CGlobal::AddStmt(CAssertExp * stmt)
{
    YY_ASSERT(stmt);
    if(isGlobal()){
        GAMMAR_ERR(stmt->lineno_,"invalid YY_ASSERTion in global scope");
    }
    CStmt * st = New<CStmt>(stmt->lineno_);
    st->type_ = 1;
    st->assert_ = stmt;
    cur_cmd->stmt_list_.push_back(st);
}

void CGlobal::AddStmt(CDeclare * stmt)
{
    YY_ASSERT(stmt);

    CStmt * st = New<CStmt>(stmt->lineno_);
    st->type_ = 2;
    st->declare_ = stmt;
}

void CGlobal::AddStmt(CFuncCall * stmt)
{
    YY_ASSERT(stmt);

    CStmt * st = New<CStmt>(stmt->lineno_);
    st->type_ = 3;
    st->func_call_ = stmt;
}

void CGlobal::CmdBegin(CVariable * var_name)
{
}

void CGlobal::CmdEnd()
{
}

