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

CSharedPtr<CDeclare> CRuntime::FindVar(std::string vname,CSharedPtr<CCmd> cmd)
{
    std::map<std::string,CSharedPtr<CDeclare> >::const_iterator wh = var_table_.end();
    if(cmd)
        wh = var_table_.find(localVarname(vname,*cmd));
    if(wh == var_table_.end())
        wh = var_table_.find(vname);
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

double CRuntime::maxPriority() const
{
    if(post_list_.empty())
        return 0;
    return Priority(post_list_.back());
}

bool CRuntime::addPostVar(const std::string & vname,CSharedPtr<CDeclare> decl,const std::string & depend)
{
    if(depend.empty()){
        addPostVar(vname,decl);
        return true;
    }
    __VnameMap::const_iterator wh = post_map_.find(depend);
    if(wh == post_map_.end()){
        RUNTIME_ERR(decl->lineno_,"no symbol '"<<depend
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
    assert(conn->IsConnection());
    if(!default_conn_)
        default_conn_ = conn;
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
    DBG_RT("processAssertExp ass="<<to_str(ass));
    DBG_RT("processAssertExp cmd="<<to_str(cmd));
    assert(cmd && cmd->IsRecv());

}

void CRuntime::processDeclare(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processDeclare decl="<<to_str(decl));
    DBG_RT("processDeclare cmd="<<to_str(cmd));
    if(!cmd){   //--------------global
        if(decl->IsSimplePost())
            processPost(decl,0);
        else if(decl->IsFixed())
            processFixed(decl,0);
        else{
            RUNTIME_ERR(decl->lineno_,"invalid declaration in global scope");
        }
    }else{
        decl->var_->varname_ = localVarname(decl->var_->varname_,*cmd);
        if(cmd->IsSend()){    //send cmd
            if(decl->IsSimplePost())
                processPost(decl,cmd);
            else if(decl->IsFixed())
                processFixed(decl,cmd);
            else if(decl->IsStreamOut())
                processStreamOut(decl,cmd);
            else{
                RUNTIME_ERR(decl->lineno_,"invalid declaration in SEND command");
            }
        }else{  //--------------recv cmd
            if(decl->IsArray())
                processArray(decl,cmd);
            if(decl->IsSimplePost())
                processPost(decl,cmd);
            else if(decl->IsAssert())
                processDeclAssert(decl,cmd);
            else if(decl->IsStreamIn())
                processStreamIn(decl,cmd);
            else{
                RUNTIME_ERR(decl->lineno_,"invalid declaration in RECV command");
            }
        }
    }
}

void CRuntime::processFunc(CSharedPtr<CFuncCall> func,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processFunc func="<<to_str(func));
    DBG_RT("processFunc cmd="<<to_str(cmd));
    if(func->IsConnection()){
        addConnection(func->Evaluate());
    }else
        func->Invoke(cmd);
}

void CRuntime::processCmd(CSharedPtr<CCmd> cmd)
{
    DBG_RT("processCmd cmd="<<to_str(cmd));
    cmd->SetByteOrder(net_byte_order_);
    for(std::vector<CSharedPtr<CStmt> >::iterator i = cmd->stmt_list_.begin();
        i != cmd->stmt_list_.end();++i)
    {
        assert(*i);
        processStmt(*i,cmd);
    }
    //send data or do something else ..........


}

void CRuntime::processArray(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processArray decl="<<to_str(decl));
    DBG_RT("processArray cmd="<<to_str(cmd));
    assert(decl->var_->array_type_);
    if(decl->var_->array_type_->expr_){
        CSharedPtr<CValue> sv = decl->var_->array_type_->expr_->Evaluate();
        if(!sv){
            RUNTIME_ERR(decl->lineno_,"cannot evaluate size of array '"
                <<decl->var_->varname_<<"'");
            return;
        }
        decl->var_->array_type_->expr_ = 0;
        if(!sv->ToInteger(decl->var_->array_type_->sz_)){
            RUNTIME_ERR(decl->lineno_,"type mismatch for size of array '"
                <<decl->var_->varname_<<"'");
            return;
        }
    }
    assert(cmd && cmd->IsRecv());
    cmd->RecvArray(decl);
}

void CRuntime::processPost(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processPost decl="<<to_str(decl));
    DBG_RT("processPost cmd="<<to_str(cmd));
    std::string vname = decl->var_->varname_;
    if(decl->IsConnection())
        processFixed(decl,0);
    else{
        assert(decl->expr_);
        decl->Evaluate();
        DBG_RT("processPost Evaluate "<<vname<<"="<<to_str(decl->val_));
        decl->eva_priority_ = maxPriority() + 1000; //解决自赋值问题
        std::string depend = decl->Depend();
        if(depend.empty()){
            decl->expr_ = 0;
            addPostVar(vname,decl);
        }else{
            if(vname == depend){
                GAMMAR_ERR(decl->lineno_,"symbol '"<<vname<<"' is self-depended");
            }
            if(!addPostVar(vname,decl,depend)){
                GAMMAR_ERR(decl->lineno_,"add symbol '"<<vname
                    <<"' to post list error, depend is '"<<depend
                    <<"'");
            }
        }
        var_table_[vname] = decl;
    }
    if(!decl->is_def_ && cmd){
        if(cmd->IsSend()){
            decl->offset_ = cmd->SendDataOffset();
            if(!cmd->SendValue(decl->val_)){
                RUNTIME_ERR(decl->lineno_,"cannot pack '"<<vname<<"'");
            }
        }else  //recv
            cmd->RecvValue(decl->val_);
    }
}

void CRuntime::processFixed(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processFixed decl="<<to_str(decl));
    DBG_RT("processFixed cmd="<<to_str(cmd));
    assert(decl->expr_);
    const std::string vname = decl->var_->varname_;
    if(decl->Evaluate() && decl->IsConnection())
        addConnection(decl->val_);
    var_table_[vname] = decl;
    if(!decl->is_def_ && cmd && cmd->IsSend() && !cmd->SendValue(decl->val_)){
        RUNTIME_ERR(decl->lineno_,"cannot pack '"<<vname<<"'");
    }
}

void CRuntime::processDeclAssert(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processDeclAssert decl="<<to_str(decl));
    DBG_RT("processDeclAssert cmd="<<to_str(cmd));
    assert(cmd && cmd->IsRecv());
    cmd->RecvAssert(decl);
}

void CRuntime::processStreamIn(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processStreamIn decl="<<to_str(decl));
    DBG_RT("processStreamIn cmd="<<to_str(cmd));
    assert(cmd && cmd->IsRecv());
}

void CRuntime::processStreamOut(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processStreamOut decl="<<to_str(decl));
    DBG_RT("processStreamOut cmd="<<to_str(cmd));
    assert(cmd && cmd->IsSend());
}
