#include <cassert>
#include <iostream>
#include "global.h"
#include "mm.h"
#include "dbg.h"
#include "util.h"
#include "errors.h"
#include "tokens.h"

CProgram::CProgram()
    : conn_defined_(false)
{}

size_t CProgram::AddQstr(const std::string qstr)
{
    size_t ret = qstr_table.size();
    qstr_table.push_back(qstr);
    return ret;
}

CSharedPtr<CVariable> CProgram::findVar(const __VarTable & vt,const std::string & name){
    typedef __VarTable::const_iterator __Iter;
    __Iter wh = vt.find(name);
    return (wh == vt.end() ? 0 : wh->second);
}

CSharedPtr<CVariable> CProgram::GetVar(const std::string & varname){
    CSharedPtr<CVariable> ret = 0;
    if(cur_cmd)
        ret = findVar(cur_cmd->var_table,varname);
    if(!ret)
        ret = findVar(var_table,varname);
    if(!ret)
        return NewVar(varname);
    ++ret->ref_count_;
    return ret;
}

CSharedPtr<CVariable> CProgram::NewVar(const std::string & varname,CSharedPtr<CVariable> old)
{
    __VarTable & vt = (isGlobal() ? var_table : cur_cmd->var_table);
    CSharedPtr<CVariable> & ret = vt[varname];
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

void CProgram::AddStmt(CSharedPtr<CAssertExp> stmt)
{
    DBG_YY("add CAssertExp="<<to_str(stmt));
    DBG_YY("cur_cmd="<<signa(cur_cmd));
    assert(stmt);
    bool good = stmt->Validate();
    good = (stmt->CheckDefined() && good);
    if(isGlobal()){
        GAMMAR_ERR(stmt->lineno_,"invalid assertion in global scope");
        good = false;
    }
    if(!good)
        return;
    CSharedPtr<CStmt> st = New<CStmt>(stmt->lineno_);
    st->type_ = 1;
    st->assert_ = stmt;
    curStmtList().push_back(st);
    DBG_YY("succ add CAssertExp="<<signa(stmt));
}

void CProgram::AddStmt(CSharedPtr<CDeclare> stmt)
{
    DBG_YY("add CDeclare="<<to_str(stmt));
    DBG_YY("cur_cmd="<<signa(cur_cmd));
    assert(stmt);
    bool good = stmt->Validate();
    good = (stmt->CheckDefined(cur_cmd) && good);
    std::string name = stmt->var_->varname_;
    if(isGlobal()){ //global scope
        if(stmt->IsLocalOnly()){
            GAMMAR_ERR(stmt->lineno_,"invalid declaration in global scope");
            good = false;
        }else if(stmt->IsConnection())
            conn_defined_ = true;
    }else{          //local scope
        if(stmt->IsStruct()){
            const std::string & name = stmt->var_->struct_name_->varname_;
            stmt->var_->struct_type_ = findCmdStruct(name);
            if(!stmt->var_->struct_type_ || !stmt->var_->struct_type_->IsStruct()){
                GAMMAR_ERR(stmt->lineno_,"symbol '"<<name<<"' is not struct, see LINE:"
                    <<stmt->var_->struct_name_->lineno_);
                good = false;
            }else
                stmt->var_->struct_name_ = 0;
        }else if(stmt->IsGlobalOnly()){
            GAMMAR_ERR(stmt->lineno_,"invalid declaration in local scope");
            good = false;
        }else if(cur_cmd->IsSend()){
            if(stmt->IsRecvOnly()){
                GAMMAR_ERR(stmt->lineno_,"invalid declaration in SEND command");
                good = false;
            }
        }else if(cur_cmd->IsRecv()){
            if(stmt->IsSendOnly()){
                GAMMAR_ERR(stmt->lineno_,"invalid declaration in RECV command");
                good = false;
            }
            if(stmt->IsSimplePost() && stmt->var_->IsRaw()){
                GAMMAR_ERR(stmt->lineno_,"recv RAW string is endless");
                good = false;
            }
        }else if(cur_cmd->IsStruct()){
            //nothing ?
        }else{
            GAMMAR_ERR(stmt->lineno_,"invalid declaration before SEND/RECV flag");
            good = false;
        }
    }
    if(!good)
        return;
    DBG_YY("add var_="<<to_str(stmt->var_));
    CurVarTable()[name] = stmt->var_;
    CSharedPtr<CStmt> st = New<CStmt>(stmt->lineno_);
    st->type_ = 2;
    st->declare_ = stmt;
    curStmtList().push_back(st);
    DBG_YY("succ add CDeclare="<<signa(stmt));
}

void CProgram::AddStmt(CSharedPtr<CFuncCall> stmt)
{
    DBG_YY("add CFuncCall="<<to_str(stmt));
    DBG_YY("cur_cmd="<<to_str(cur_cmd));
    assert(stmt);
    bool good = stmt->Validate();
    good = (stmt->CheckDefined() && good);
    if(!stmt->HasSideEffect()){
        GAMMAR_ERR(stmt->lineno_,"useless function");
        good = false;
    }
    if(isGlobal()){ //global
        if(stmt->IsLocalOnly()){
            GAMMAR_ERR(stmt->lineno_,"invalid function in global scope");
            good = false;
        }else if(stmt->IsConnection()){
            if(conn_defined_){
                GAMMAR_ERR(stmt->lineno_,"connection will never be used");
                good = false;
            }else
                conn_defined_ = true;
        }
    }else{          //local
        if(stmt->IsGlobalOnly()){
            GAMMAR_ERR(stmt->lineno_,"invalid function in local scope");
            good = false;
        }else if(cur_cmd->IsStruct()){
            if(stmt->IsSendRecv()){
                GAMMAR_ERR(stmt->lineno_,"invalid SEND/RECV flag for struct");
                good = false;
            }
        }else{  //cmd
            int sr = stmt->IsSendRecv();
            if(sr){
                if(!conn_defined_){
                    GAMMAR_ERR(stmt->lineno_,"no connection yet");
                    good = false;
                }else if(!cur_cmd->cmd_send_flag_){
                    cur_cmd->cmd_send_flag_ = sr;
                }else if(sr != cur_cmd->cmd_send_flag_){
                    GAMMAR_ERR(stmt->lineno_,"cannot change SEND/RECV flag");
                    good = false;
                }
            }
        }
    }
    if(!good)
        return;
    CSharedPtr<CStmt> st = New<CStmt>(stmt->lineno_);
    st->type_ = 3;
    st->func_call_ = stmt;
    curStmtList().push_back(st);
    DBG_YY("succ add CFuncCall="<<signa(stmt));
}

void CProgram::CmdStructBegin(CSharedPtr<CVariable> var,bool is_cmd)
{
    DBG_YY("new command CVariable="<<to_str(var));
    const char * const CMD_STRUCT = (is_cmd ? "command" : "struct");
    std::string name;
    int var_lineno = LINE_NO;
    if(var){
        name = var->varname_;
        var_lineno = var->lineno_;
    }
    bool good = true;
    if(!isGlobal()){
        GAMMAR_ERR(LINE_NO,"cannot define "<<CMD_STRUCT<<" '"<<name
            <<"' in local scope of '"<<cur_cmd->struct_name_<<"', see LINE:"
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
            var = 0;
        }
    }
    if(!good)
        return;
    CSharedPtr<CCmdStruct> & cmd = cmd_table[name];
    if(cmd){
        GAMMAR_ERR(LINE_NO,"cannot redefine "<<CMD_STRUCT<<" '"<<name<<"', see LINE:"
            <<cmd->lineno_);
        return;
    }
    DBG_YY("cmd="<<to_str(cmd)<<", cur_cmd="<<to_str(cur_cmd));
    cur_cmd = New<CCmdStruct>(LINE_NO);
    cmd = cur_cmd;
    cmd->cmd_send_flag_ = (is_cmd ? 0 : 3);
    cmd->struct_name_ = name;
    CSharedPtr<CStmt> st = New<CStmt>(LINE_NO);
    st->type_ = 4;
    st->cmd_struct_ = cmd;
    if(cmd->IsCmd())
        global_stmts.push_back(st);
    DBG_YY("succ new "<<CMD_STRUCT<<"="<<signa(cmd));
}

void CProgram::CmdStructEnd(bool is_cmd)
{
    const char * const CMD_STRUCT = (is_cmd ? "command" : "struct");
    if(isGlobal()){
        GAMMAR_ERR(LINE_NO,"invalid end of "<<CMD_STRUCT);
    }
    DBG_YY("end "<<CMD_STRUCT<<"="<<signa(cur_cmd));
    if(cur_cmd->cmd_send_flag_ == 0){
        GAMMAR_ERR(LINE_NO,"missing SEND/RECV flag for command '"
            <<cur_cmd->struct_name_<<"', see LINE:"<<cur_cmd->lineno_);
        global_stmts.pop_back();    //保持struct_name_在cmd_table内
    }
    cur_cmd = 0;
}

CSharedPtr<CCmdStruct> CProgram::findCmdStruct(const std::string & name) const
{
    typedef std::map<std::string,CSharedPtr<CCmdStruct> >::const_iterator __Iter;
    __Iter wh = cmd_table.find(name);
    return (wh == cmd_table.end() ? 0 : wh->second);
}
