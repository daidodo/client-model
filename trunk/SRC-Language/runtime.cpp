#include "global.h"
#include "functions.h"
#include "dbg.h"

CRuntime::CRuntime()
    : argc_(0)
    , argv_(0)
    , cur_byte_order_(true)
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

std::string CRuntime::RealVarname(const std::string & name)
{
    return name.substr(0,name.find('$'));
}

double CRuntime::maxPriority() const
{
    if(post_list_.empty())
        return 0;
    return Priority(post_list_.back());
}

void CRuntime::postEvaluate(CSharedPtr<CCmd> cmd)
{
    typedef CSharedPtr<CValue>          __ValPtr;
    typedef std::list<__ValPtr>         __ValList;  //可能会在同一个offset，插入多个数据
    typedef std::map<size_t,__ValList,std::greater<size_t> >  __ValSeq;
    assert(cmd && cmd->IsSend());
    __ValSeq post_insert_list;
    for(__VnameList::iterator i = post_list_.begin();i != post_list_.end();++i){
        CSharedPtr<CDeclare> decl = FindVar(*i);
        if(!decl){
            INTERNAL_ERR("declaration for '"<<*i<<"' not found");
            continue;
        }
        //set byte order
        if(decl->post_byte_order_ != cur_byte_order_)
            InvokeBO(decl->post_byte_order_,cmd);
        //post set value
        if(decl->IsSimplePost()){
            CSharedPtr<CValue> v = decl->Evaluate();
            if(decl->is_def_ || decl->offset_ < 0)  //def or global var
                continue;
            if(v && !cmd->PostPutValue(v,decl->offset_)){
                INTERNAL_ERR("cannot post pack '"<<*i<<"'");
            }
        }else if(decl->IsStreamOut()){
            if(!decl->val_){
                RUNTIME_ERR(decl->lineno_,"left hand variable is not initialized");
                continue;
            }
            assert(decl->expr_);
            CSharedPtr<CValue> v = decl->expr_->Evaluate();
            if(!v){
                RUNTIME_ERR(decl->lineno_,"cannot evaluate right hand expression");
                continue;
            }
            if(decl->val_->StreamOut(*v,decl->lineno_) && !decl->is_def_)    //post insert越后越好，因为它改变了其他数据的偏移
                post_insert_list[decl->offset_].push_front(decl->val_);
        }else{
            INTERNAL_ERR("invalid post evaluation for symbol '"<<*i<<"'");
        }
    }
    post_list_.clear();
    //安全的post insert
    for(__ValSeq::const_iterator i = post_insert_list.begin();i != post_insert_list.end();++i){
        const size_t off = i->first;
        for(__ValList::const_iterator v = i->second.begin();v != i->second.end();++v){
            if(!cmd->PostInsertValue(*v,off)){
                INTERNAL_ERR("cannot post insert value "<<(*v)->ShowValue());
            }
        }
    }
}

void CRuntime::addPostVar(const std::string & vname,CSharedPtr<CDeclare> decl,const std::string & depend)
{
    assert(!depend.empty());
    __VnameMap::const_iterator wh = post_map_.find(depend);
    __VnameIter next;
    if(wh == post_map_.end()){
        next = post_list_.end();
        if(!post_list_.empty())
            decl->eva_priority_ = Priority(post_list_.back());
        decl->eva_priority_ += 1000;
    }else{
        next = wh->second;
        decl->eva_priority_ = Priority(*next);
        ++next;
        if(next == post_list_.end())
            decl->eva_priority_ += 1000;
        else{
            decl->eva_priority_ += Priority(*next);
            decl->eva_priority_ /= 2;
        }
    }
    decl->post_byte_order_ = cur_byte_order_;
    post_map_[vname] = post_list_.insert(next,vname);
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
    if(!ass->Assert()){
        cmd->DumpRecvData();
        ASSERT_FAIL(ass->lineno_,"");
    }
}

void CRuntime::processDeclare(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processDeclare decl="<<to_str(decl));
    DBG_RT("processDeclare cmd="<<to_str(cmd));
    if(!cmd){   //global
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
            else if(decl->IsArray())
                processArray(decl,cmd);
            else{
                RUNTIME_ERR(decl->lineno_,"invalid declaration in SEND command");
            }
        }else{  //recv cmd
            if(decl->IsArray())
                processArray(decl,cmd);
            else if(decl->IsSimplePost())
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
        CSharedPtr<CValue> conn = func->Evaluate();
        if(!conn){
            RUNTIME_ERR(func->lineno_,"cannot evaluate function");
        }else
            addConnection(conn);
    }else
        func->Invoke(cmd);
}

void CRuntime::processCmd(CSharedPtr<CCmd> cmd)
{
    DBG_RT("processCmd cmd="<<to_str(cmd));
    if(cmd->IsRecv()){
        SHOW("  RECV command '"<<cmd->cmd_name_<<"'");
    }
    cmd->SetByteOrder(cur_byte_order_);
    for(cmd->cur_stmt_index_ = 0;cmd->cur_stmt_index_ < cmd->stmt_list_.size();
        ++cmd->cur_stmt_index_)
    {
        assert(cmd->stmt_list_[cmd->cur_stmt_index_]);
        processStmt(cmd->stmt_list_[cmd->cur_stmt_index_],cmd);
    }
    if(cmd->IsInArray()){
        RUNTIME_ERR(cmd->array_range_.back().lineno_,"missing END ARRAY");
    }
    if(global().err_count_)
        throw 0;
    if(cmd->IsSend()){
        if(cmd->begin_list_){
            InvokeBeginEnd(false,cmd->begin_list_,cmd->endlineno_,cmd);
            cmd->begin_list_ = 0;
        }
        postEvaluate(cmd);
        //print data buffer
        std::vector<char> buf;
        cmd->outds_.ExportData(buf);
        SHOW("  SEND command '"<<cmd->cmd_name_<<"' data =");
        SHOW(DumpFormat(buf));
        //send data
#if __REAL_CONNECT
        cmd->SendData(buf);
#endif
    }else   //recv
        cmd->DumpRecvData();
}

void CRuntime::processArray(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processArray decl="<<to_str(decl));
    DBG_RT("processArray cmd="<<to_str(cmd));
    assert(cmd);
    assert(decl->var_->array_type_);
    const std::string & vname = decl->var_->varname_;
    if(decl->var_->array_type_->sz_expr_){
        CSharedPtr<CValue> sv = decl->var_->array_type_->sz_expr_->Evaluate();
        if(!sv){
            RUNTIME_ERR(decl->lineno_,"cannot evaluate size of array '"
                <<RealVarname(vname)<<"'");
            return;
        }
        if(!sv->ToInteger(decl->var_->array_type_->sz_)){
            RUNTIME_ERR(decl->lineno_,"type mismatch for size of array '"
                <<RealVarname(vname)<<"'");
            return;
        }
    }else if(cmd->IsSend()){
        RUNTIME_ERR(decl->lineno_,"array size is unknown in SEND command");
        return;
    }
    decl->val_ = decl->var_->Initial(decl->lineno_);
    if(!decl->val_){
        ASSERT_FAIL(decl->lineno_,"cannot initialize '"<<RealVarname(vname)
            <<"'");
    }
    if(cmd->IsSend() && !cmd->PutArray(decl)){
        RUNTIME_ERR(decl->lineno_,"cannot pack array '"<<RealVarname(vname)
            <<"'");
    }else if(cmd->IsRecv() && !cmd->GetArray(decl)){
        cmd->DumpRecvData();
        ASSERT_FAIL(decl->lineno_,"recv '"<<RealVarname(vname)<<"' failed");
    }
}

void CRuntime::processPost(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processPost decl="<<to_str(decl));
    DBG_RT("processPost cmd="<<to_str(cmd));
    const std::string & vname = decl->var_->varname_;
    if(decl->IsConnection())
        return processFixed(decl,0);
    assert(decl->expr_);
    if(!decl->Evaluate())
        return;
    DBG_RT("processPost Evaluate "<<vname<<"="<<to_str(decl->val_));
    var_table_[vname] = decl;
    if(!cmd)
        return;
    if(cmd->IsSend()){  //send cmd
        if(decl->val_->IsInteger()){    //必须是发送命令里的数值类型
            if(cmd->IsInArray()){
                RUNTIME_ERR(decl->lineno_,"post evaluation in ARRAY is not supported yet, please using :=");
            }else{
                decl->eva_priority_ = maxPriority() + 1000; //解决自赋值问题
                std::string depend = decl->Depend();
                if(depend.empty()){
                    decl->eva_priority_ = 0;
                    //decl->expr_ = 0;
                }else{
                    if(vname == depend){
                        GAMMAR_ERR(decl->lineno_,"symbol '"<<RealVarname(vname)
                            <<"' is self-depended");
                    }
                    addPostVar(vname,decl,depend);
                }
            }
        }
        if(!decl->is_def_){
            decl->offset_ = cmd->SendDataOffset();
            if(!cmd->PutValue(decl->val_)){
                RUNTIME_ERR(decl->lineno_,"cannot pack '"<<RealVarname(vname)<<"'");
            }
        }
    }else{  //recv cmd
        if(!decl->is_def_){
            if(!cmd->GetValue(decl->val_,decl->lineno_)){
                cmd->DumpRecvData();
                ASSERT_FAIL(decl->lineno_,"recv '"<<RealVarname(vname)<<"' failed");
            }
            SHOW(RealVarname(vname)<<cmd->ArrayIndexString()<<" = "
                <<decl->val_->ShowValue());
        }
    }
}

void CRuntime::processFixed(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processFixed decl="<<to_str(decl));
    DBG_RT("processFixed cmd="<<to_str(cmd));
    const std::string & vname = decl->var_->varname_;
    if(decl->Evaluate()){
        if(decl->IsConnection())
            addConnection(decl->val_);
        else{
            var_table_[vname] = decl;
            if(!decl->is_def_ && cmd && cmd->IsSend() && !cmd->PutValue(decl->val_)){
                RUNTIME_ERR(decl->lineno_,"cannot pack '"<<RealVarname(vname)<<"'");
            }
            decl->expr_ = 0;
        }
    }
}

void CRuntime::processDeclAssert(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processDeclAssert decl="<<to_str(decl));
    DBG_RT("processDeclAssert cmd="<<to_str(cmd));
    const std::string & vname = decl->var_->varname_;
    decl->val_ = decl->var_->Initial(decl->lineno_);
    if(!decl->val_){
        RUNTIME_ERR(decl->lineno_,"cannot initialize '"<<RealVarname(vname)
            <<"'");
        return;
    }
    assert(decl->expr_);
    CSharedPtr<CValue> v = decl->expr_->Evaluate();
    if(!v){
        RUNTIME_ERR(decl->lineno_,"cannot evaluate right hand expression");
        return;
    }
    //decl->expr_ = 0;
    assert(cmd && cmd->IsRecv());
    if(!cmd->GetAssert(decl,v)){
        cmd->DumpRecvData();
        ASSERT_FAIL(decl->lineno_,"");
    }
    var_table_[vname] = decl;
}

void CRuntime::processStreamIn(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processStreamIn decl="<<to_str(decl));
    DBG_RT("processStreamIn cmd="<<to_str(cmd));
    const std::string & vname = decl->var_->varname_;
    decl->val_ = decl->var_->Initial(decl->lineno_);
    if(!decl->val_){
        RUNTIME_ERR(decl->lineno_,"cannot initialize '"<<RealVarname(vname)
            <<"'");
        return;
    }
    assert(decl->expr_);
    CSharedPtr<CValue> v = decl->expr_->Evaluate();
    if(!v){
        RUNTIME_ERR(decl->lineno_,"cannot evaluate right hand expression");
        return;
    }
    //decl->expr_ = 0;
    assert(cmd && cmd->IsRecv());
    if(!cmd->GetStreamIn(decl,v)){
        cmd->DumpRecvData();
        ASSERT_FAIL(decl->lineno_,"");
    }
    SHOW(RealVarname(vname)<<cmd->ArrayIndexString()<<" = "
        <<decl->val_->ShowValue());
    var_table_[vname] = decl;
}

void CRuntime::processStreamOut(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd)
{
    DBG_RT("processStreamOut decl="<<to_str(decl));
    DBG_RT("processStreamOut cmd="<<to_str(cmd));
    assert(cmd && cmd->IsSend());
    if(!cmd->BeginEmpty()){
        RUNTIME_ERR(decl->lineno_,"invalid stream out between BEGIN/END");
        return;
    }else if(cmd->IsInArray()){
        RUNTIME_ERR(decl->lineno_,"invalid stream out in ARRAY");
        return;
    }
    const std::string & vname = decl->var_->varname_;
    decl->val_ = decl->var_->Initial(decl->lineno_);
    if(!decl->val_){
        RUNTIME_ERR(decl->lineno_,"cannot initialize '"<<RealVarname(vname)<<"'");
        return;
    }
    var_table_[vname] = decl;
    decl->offset_ = cmd->SendDataOffset();
    decl->eva_priority_ = maxPriority() + 1000; //解决自赋值问题
    std::string depend = decl->Depend();
    if(depend.empty()){
        assert(decl->expr_);
        decl->eva_priority_ = 0;
        CSharedPtr<CValue> v = decl->expr_->Evaluate();
        if(!v){
            RUNTIME_ERR(decl->lineno_,"cannot evaluate right hand expression");
            return;
        }
        decl->expr_ = 0;
        if(decl->val_->StreamOut(*v,decl->lineno_) && !decl->is_def_ &&
            !cmd->PutValue(decl->val_))
        {
            RUNTIME_ERR(decl->lineno_,"cannot pack value "<<v->ShowValue());
            return;
        }
    }else{
        if(vname == depend){
            GAMMAR_ERR(decl->lineno_,"symbol '"<<RealVarname(vname)<<"' is self-depended");
        }
        addPostVar(vname,decl,depend);
    }
}
