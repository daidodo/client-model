#include <iostream>
#include <cassert>
#include "errors.h"
#include "runtime.h"
#include "util.h"
#include "dbg.h"

void CRuntime::Interpret(CProgram & program)
{
    for(__StmtList::iterator i = program.global_stmts.begin();
        i != program.global_stmts.end();++i)
    {
        assert(*i);
        DBG_RT("Interpret stmt="<<to_str(*i));
        switch((*i)->type_){
            case 1:
                GAMMAR_ERR((*i)->lineno_,"invalid assertion in global scope");
                break;
            case 2:
                assert((*i)->declare_);
                processDeclare((*i)->declare_);
                break;
            case 3:
                assert((*i)->func_call_);
                processFunc((*i)->func_call_);
                break;
            case 4:
                assert((*i)->cmd_);
                processCmd((*i)->cmd_);
                break;
            default:
                GAMMAR_ERR((*i)->lineno_,"(internal error)invalid statement type("
                    <<(*i)->type_<<")");
        }
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

bool CRuntime::addPostVar(const std::string & vname,CSharedPtr<CDeclare> decl,const std::string & depend)
{
    if(depend.empty()){
        addPostVar(vname,decl);
        return true;
    }
    __VnameMap::const_iterator wh = post_map_.find(depend);
    if(wh == post_map_.end()){
        GAMMAR_ERR(decl->lineno_,"no symbol '"<<depend
            <<"' in post map(internal error)");
        return false;
    }
    __VnameIter next = wh->second;
    double dep = Priority(*next);
    ++next;
    if(next == post_list_.end()){
        decl->eva_priority_ = dep * 2;
    }else
        decl->eva_priority_ = (dep + Priority(*next)) / 2;
    post_map_[vname] = post_list_.insert(next,vname);
    return true;
}

void CRuntime::addPostVar(const std::string & vname,CSharedPtr<CDeclare> decl)
{
    if(post_list_.empty())
        decl->eva_priority_ = 10000;
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

void CRuntime::processDeclare(CSharedPtr<CDeclare> decl)
{
    DBG_RT("processDeclare decl="<<to_str(decl));
    decl->var_->varname_.push_back('$');
    switch(decl->type_){
        case 1:                 //array
            GAMMAR_ERR(decl->lineno_,"invalid array in global scope");
            break;
        case 2:case 3:case 4:   //post
            processPost(decl);
            break;
        case 5:case 6:          //fixed
            processFixed(decl);
            break;
        case 7:
            GAMMAR_ERR(decl->lineno_,"invalid assertion in global scope");
            break;
        case 8:case 9:
            GAMMAR_ERR(decl->lineno_,"invalid stream in global scope");
            break;
        default:
            GAMMAR_ERR(decl->lineno_,"invalid declare type("
                <<decl->type_<<")(internal error)");
    }
}

void CRuntime::processFunc(CSharedPtr<CFuncCall> func)
{
    DBG_RT("processFunc func="<<to_str(func));
    if(!func->HasSideEffect()){
        GAMMAR_ERR(func->lineno_,"useless function");
        return;
    }
    if(func->IsLocalOnly()){
        GAMMAR_ERR(func->lineno_,"invalid function in global scope");
        return;
    }
    if(func->IsConnection()){
    }
}

void CRuntime::processCmd(CSharedPtr<CCmd> cmd)
{
}

void CRuntime::processPost(CSharedPtr<CDeclare> decl)
{
    DBG_RT("processPost decl="<<to_str(decl));
    if(decl->IsConnection()){
        processFixed(decl);
    }else{
        std::string vname = decl->var_->varname_;
        std::string depend = decl->Depend();
        if(depend.empty()){
            decl->val_ = decl->expr_->Evaluate();
            DBG_RT("processPost Evaluate decl="<<to_str(decl->val_));
            if(!decl->val_){
                GAMMAR_ERR(decl->lineno_,"cannot evaluate '"<<vname
                    <<"'");
            }
            decl->expr_ = 0;
            addPostVar(vname,decl);
        }else if(!addPostVar(vname,decl,depend)){
            GAMMAR_ERR(decl->lineno_,"add symbol '"<<vname
                <<"' to post map error, depend '"<<depend
                <<"'(internal error)");
        }
        var_table_[vname] = decl;
    }
}

void CRuntime::processFixed(CSharedPtr<CDeclare> decl)
{
    DBG_RT("processFixed decl="<<to_str(decl));
    std::string vname = decl->var_->varname_;
    decl->val_ = decl->expr_->Evaluate();
    DBG_RT("processFixed Evaluate decl="<<to_str(decl->val_));
    if(decl->val_){
        if(decl->IsConnection())
            addConnection(decl->val_);
    }else{
        GAMMAR_ERR(decl->lineno_,"cannot evaluate '"<<vname
            <<"'");
    }
    var_table_[vname] = decl;
}
