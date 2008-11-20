#include <iostream>
#include <cassert>
#include "errors.h"
#include "runtime.h"
#include "util.h"
#include "dbg.h"

CRuntime::CRuntime()
    : net_byte_order_(true)
{}


void CRuntime::Interpret(CProgram & program)
{
    for(std::vector<CSharedPtr<CStmt> >::iterator i = program.global_stmts.begin();
        i != program.global_stmts.end();++i)
    {
        assert(*i);
        processStmt(*i,0);
    }
}

CSharedPtr<CDeclare> CRuntime::FindVar(std::string vname)
{
    std::map<std::string,CSharedPtr<CDeclare> >::const_iterator wh = var_table_.find(vname);
    if(wh == var_table_.end()){
        vname.push_back('$');
        wh = var_table_.find(vname);
    }
    return (wh == var_table_.end() ? 0 : wh->second);
}

double CRuntime::Priority(const std::string & vname) const
{
    if(vname.empty())
        return 0;
    std::map<std::string,CSharedPtr<CDeclare> >::const_iterator wh = var_table_.find(vname);
    assert(wh != var_table_.end());
    return wh->second->eva_priority_;
}

bool CRuntime::IsPost(const std::string & vname) const
{
    std::map<std::string,CSharedPtr<CDeclare> >::const_iterator wh = var_table_.find(vname);
    assert(wh != var_table_.end());
    return wh->second->IsPost();
}

std::string CRuntime::localVarname(const std::string & name,const CCmd & cmd)
{
    std::string ret = name;
    size_t pos = name.find('$');
    if(pos == std::string::npos){
        ret.push_back('$');
        ret += cmd.cmd_name_;
    }
    return ret;
}

bool CRuntime::addPostVar(const std::string & vname,CSharedPtr<CDeclare> decl,const std::string & depend)
{
    if(depend.empty()){
        addPostVar(vname,decl);
        return true;
    }
    __VnameMap::const_iterator wh = post_map_.find(depend);
    if(wh == post_map_.end()){
        RUNTIME_ERR("no symbol '"<<depend
            <<"' in post map(internal error)");
        return false;
    }
    __VnameIter next = wh->second;
    double dep = Priority(*next);
    ++next;
    if(next == post_list_.end()){
        decl->eva_priority_ = dep + 1000;
    }else
        decl->eva_priority_ = (dep + Priority(*next)) / 2;
    post_map_[vname] = post_list_.insert(next,vname);
    return true;
}

void CRuntime::addPostVar(const std::string & vname,CSharedPtr<CDeclare> decl)
{
    if(post_list_.empty())
        decl->eva_priority_ = 1000;
    else
        decl->eva_priority_ = Priority(post_list_.front()) / 2;
    post_list_.push_front(vname);
    post_map_[vname] = post_list_.begin();
}

void CRuntime::addConnection(CSharedPtr<CValue> conn)
{
    if(!default_tcp_ && !default_udp_){
        if(conn->tcp_){         //tcp
            default_tcp_ = conn->tcp_;
        }else if(conn->udp_){   //udp
            default_udp_ = conn->udp_;
        }else
            assert(0);
    }
}

void CRuntime::processStmt(CSharedPtr<CStmt> stmt,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processStmt stmt="<<to_str(stmt));
    DBG_RT("processStmt cmd="<<to_str(cmd));
    if(!cmd){   //----------------global
        if(stmt->declare_)
            processDeclare(stmt->declare_,0);
        else if(stmt->func_call_)
            processFunc(stmt->func_call_,0);
        else if(stmt->cmd_)
            processCmd(stmt->cmd_);
    }else if(cmd->IsSend()){    //send cmd
        if(stmt->declare_)
            processDeclare(stmt->declare_,cmd);
        else if(stmt->func_call_)
            processFunc(stmt->func_call_,cmd);
    }else{  //--------------------recv cmd
        if(stmt->assert_)
            processAssertExp(stmt->assert_,cmd);
        else if(stmt->declare_)
            processDeclare(stmt->declare_,cmd);
        else if(stmt->func_call_)
            processFunc(stmt->func_call_,cmd);
    }
}

void CRuntime::processAssertExp(CSharedPtr<CAssertExp> ass,CSharedPtr<CCmd> cmd)
{
    if(!cmd){   //----------------global
    }else if(cmd->IsSend()){    //send cmd
    }else{  //--------------------recv cmd
    }

}

void CRuntime::processDeclare(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processDeclare decl="<<to_str(decl));
    if(!cmd){   //--------------global
        if(decl->IsSimplePost())
            processPost(decl,0);
        else if(decl->IsFixed())
            processFixed(decl,0);
        else{
            RUNTIME_ERR("invalid declaration in global scope");
        }
    }else{
        decl->var_->varname_ = localVarname(decl->var_->varname_,*cmd);
        if(cmd->IsSend()){    //send cmd
            if(decl->IsSimplePost())
                processPost(decl,cmd);
            else if(decl->IsFixed())
                processFixed(decl,cmd);
            else if(decl->IsStreamIn())
                processStreamIn(decl,cmd);
            else{
                RUNTIME_ERR("invalid declaration in SEND command");
            }
        }else{  //--------------recv cmd
            if(decl->IsArray())
                processArray(decl,cmd);
            if(decl->IsSimplePost())
                processPost(decl,cmd);
            else if(decl->IsAssert())
                processDeclAssert(decl,cmd);
            else if(decl->IsStreamOut())
                processStreamOut(decl,cmd);
            else{
                RUNTIME_ERR("invalid declaration in RECV command");
            }
        }
    }
}

void CRuntime::processFunc(CSharedPtr<CFuncCall> func,CSharedPtr<CCmd> cmd)
{
    if(!cmd){   //----------------global
    }else if(cmd->IsSend()){    //send cmd
    }else{  //--------------------recv cmd
    }
    //DBG_RT("processFunc func="<<to_str(func));
    //if(!func->HasSideEffect()){
    //    GAMMAR_ERR(func->lineno_,"useless function");
    //    return false;
    //}else if(func->IsLocalOnly()){
    //    if(!cmd){
    //        GAMMAR_ERR(func->lineno_,"invalid function in global scope");
    //        return false;
    //    }
    //}else if(func->IsConnection()){
    //    if(cmd){
    //        GAMMAR_ERR(func->lineno_,"invalid connection in local scope");
    //        return false;
    //    }else if(default_tcp_ || default_tcp_){
    //        GAMMAR_ERR(func->lineno_,"connection will never be used");
    //        return false;
    //    }else
    //        addConnection(func->Evaluate());
    //    return false;
    //}   //HBO NBO
    //return true;
}

void CRuntime::processCmd(CSharedPtr<CCmd> cmd)
{
    for(std::vector<CSharedPtr<CStmt> >::iterator i = cmd->stmt_list_.begin();
        i != cmd->stmt_list_.end();++i)
    {
        assert(*i);
        processStmt(*i,cmd);
    }
    //send data or something else ..........
}

void CRuntime::processArray(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
}

void CRuntime::processPost(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    if(!cmd){   //----------------global
    }else if(cmd->IsSend()){    //send cmd
    }else{  //--------------------recv cmd
    }
    //DBG_RT("processPost decl="<<to_str(decl));
    //if(decl->IsConnection()){
    //    processFixed(decl);
    //    return false;
    //}else{
    //    std::string vname = decl->var_->varname_;
    //    std::string depend = decl->Depend();
    //    if(depend.empty()){
    //        decl->val_ = decl->expr_->Evaluate();
    //        DBG_RT("processPost Evaluate decl="<<to_str(decl->val_));
    //        if(!decl->val_){
    //            GAMMAR_ERR(decl->lineno_,"cannot evaluate '"<<vname
    //                <<"'");
    //            return false;
    //        }
    //        decl->expr_ = 0;
    //        addPostVar(vname,decl);
    //    }else if(!addPostVar(vname,decl,depend)){
    //        GAMMAR_ERR(decl->lineno_,"add symbol '"<<vname
    //            <<"' to post map error, depend '"<<depend
    //            <<"'(internal error)");
    //        return false;
    //    }
    //    var_table_[vname] = decl;
    //}
    //return !decl->is_def_;
}

void CRuntime::processFixed(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    if(!cmd){   //----------------global
    }else if(cmd->IsSend()){    //send cmd
    }else{  //--------------------recv cmd
    }
    //DBG_RT("processFixed decl="<<to_str(decl));
    //std::string vname = decl->var_->varname_;
    //decl->val_ = decl->expr_->Evaluate();
    //DBG_RT("processFixed Evaluate decl="<<to_str(decl->val_));
    //if(decl->val_){
    //    if(decl->IsConnection())
    //        addConnection(decl->val_);
    //}else{
    //    GAMMAR_ERR(decl->lineno_,"cannot evaluate '"<<vname
    //        <<"'");
    //    return false;
    //}
    //var_table_[vname] = decl;
    //return !decl->is_def_;
}

void CRuntime::processDeclAssert(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
}

void CRuntime::processStreamIn(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
}

void CRuntime::processStreamOut(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
}
