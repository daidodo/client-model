#include <iostream>
#include "global.h"
#include "mm.h"
#include "dbg.h"
#include "util.h"
#include "tokens.h"

//__Del
template<class T>
CProgram::__Del<T>::~__Del()
{
    Delete(p_);
}

//CProgram
CProgram::CProgram()
    : tcp_default(true)
    , cur_cmd(0)
{}

CProgram::~CProgram(){
    //vars and stmts
    for(__VarTable::iterator i = var_table.begin();i != var_table.end();++i)
        Delete(i->second);
    std::for_each(global_stmts.begin(),global_stmts.end(),Delete<CStmt>);
    //connections
    std::for_each(tcp_table.begin(),tcp_table.end(),Delete<CTcp>);
    std::for_each(udp_table.begin(),udp_table.end(),Delete<CUdp>);
}

size_t CProgram::AddQstr(const std::string qstr)
{
    size_t ret = qstr_table.size();
    qstr_table.push_back(qstr);
    return ret;
}

CVariable * CProgram::findVar(const __VarTable & vt,const std::string & name){
    typedef __VarTable::const_iterator __Iter;
    __Iter wh = vt.find(name);
    return (wh == vt.end() ? 0 : wh->second);
}

CVariable * CProgram::GetVar(const std::string & varname){
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

CVariable * CProgram::NewVar(const std::string & varname,CVariable * old)
{
    __VarTable & vt = (isGlobal() ? var_table : cur_cmd->var_table);
    CVariable *& ret = vt[varname];
    assert(!ret);
    ret = New<CVariable>(LINE_NO);
    ret->varname_ = varname;
    ret->host_cmd_ = cur_cmd;
    if(old)
        --old->ref_count_;
    return ret;
}

const std::string & CProgram::GetQstr(size_t i) const{
    assert(i < qstr_table.size());
    return qstr_table[i];
}

void CProgram::AddStmt(CAssertExp * stmt)
{
    DBG_GMM("add CAssertExp="<<to_str(stmt));
    DBG_GMM("cur_cmd="<<signa(cur_cmd));
    YY_ASSERT(stmt);
    __Del<CAssertExp> g(stmt);
    bool good = stmt->Validate();
    good = (stmt->CheckDefined() && good);
    if(isGlobal()){
        GAMMAR_ERR(stmt->lineno_,"invalid assertion in global scope");
        good = false;
    }
    if(!good)
        return;
    CStmt * st = New<CStmt>(stmt->lineno_);
    st->type_ = 1;
    st->assert_ = stmt;
    cur_cmd->stmt_list_.push_back(st);
    g.Succ();
    DBG_GMM("succ add CAssertExp="<<signa(stmt));
}

void CProgram::AddStmt(CDeclare * stmt)
{
    DBG_GMM("add CDeclare="<<to_str(stmt));
    DBG_GMM("cur_cmd="<<signa(cur_cmd));
    YY_ASSERT(stmt);
    __Del<CDeclare> g(stmt);
    bool good = stmt->Validate();
    good = (stmt->CheckDefined(cur_cmd) && good);
    std::string name = stmt->var_->varname_;
    if(isGlobal()){ //global scope
        if(stmt->IsAssert()){
            GAMMAR_ERR(stmt->lineno_,"invalid assertion for '"<<name
                <<"' in global scope");
            good = false;
        }
    }else{          //local scope
        if(stmt->IsGlobalOnly()){
            GAMMAR_ERR(stmt->lineno_,"invalid declaration of '"<<name
                <<"' in local scope");
            good = false;
        }
    }
    if(!good)
        return;
    DBG_GMM("add var_="<<to_str(stmt->var_));
    CurVarTable()[name] = stmt->var_;
    CStmt * st = New<CStmt>(stmt->lineno_);
    st->type_ = 2;
    st->declare_ = stmt;
    g.Succ();
    DBG_GMM("succ add CDeclare="<<signa(stmt));
}

void CProgram::AddStmt(CFuncCall * stmt)
{
    DBG_GMM("add CFuncCall="<<to_str(stmt));
    DBG_GMM("cur_cmd="<<signa(cur_cmd));
    YY_ASSERT(stmt);
    __Del<CFuncCall> g(stmt);
    bool good = stmt->CheckDefined();
    if(!good)
        return;
    CStmt * st = New<CStmt>(stmt->lineno_);
    st->type_ = 3;
    st->func_call_ = stmt;
    g.Succ();
    DBG_GMM("succ add CFuncCall="<<signa(stmt));
}

void CProgram::CmdBegin(CVariable * var)
{
    DBG_GMM("new command CVariable="<<to_str(var));
    std::string name;
    int var_lineno = LINE_NO;
    if(var){
        name = var->varname_;
        var_lineno = var->lineno_;
    }
    bool good = true;
    if(!isGlobal()){
        GAMMAR_ERR(LINE_NO,"cannot define command '"<<name
            <<"' in local scope of '"<<cur_cmd->cmd_name_<<"', see LINE:"
            <<var_lineno);
        good = false;
    }
    if(var){
        if(!var->Is1stDefine()){
            GAMMAR_ERR(LINE_NO,"cannot redefine symbol '"<<name<<"', see LINE:"
                <<var_lineno);
            good = false;
        }else{
            var_table.erase(name);
            Delete(var);
        }
    }
    if(!good)
        return;
    CCommand *& cmd = cmd_table[name];
    if(cmd){
        GAMMAR_ERR(LINE_NO,"cannot redefine command '"<<name<<"', see LINE:"
            <<cmd->lineno_);
        good = false;
    }
    if(!good)
        return;
    cmd = cur_cmd = New<CCommand>(LINE_NO);
    cmd->cmd_name_ = name;
    CStmt * st = New<CStmt>(LINE_NO);
    st->type_ = 4;
    st->cmd_ = cmd;
    DBG_GMM("succ new command="<<signa(cmd));
}

void CProgram::CmdEnd()
{
    if(isGlobal()){
        GAMMAR_ERR(LINE_NO,"invalid end of command");
    }
    DBG_GMM("end command="<<signa(cur_cmd));
    cur_cmd = 0;
}

CCommand * CProgram::findCmd(const std::string & name) const
{
    typedef std::map<std::string,CCommand *>::const_iterator __Iter;
    __Iter wh = cmd_table.find(name);
    return (wh == cmd_table.end() ? 0 : wh->second);
}
