#include "global.h"
#include "dbg.h"
#include "functions.h"

__ValuePtr EvaluateU8(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = DT_U8;
    if(!args.empty() && !args[0]->ToInteger(ret->u8_)){
        RUNTIME_ERR(lineno,"invalid conversion to U8");
    }
    return ret;
}

__ValuePtr EvaluateS8(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = DT_S8;
    if(!args.empty() && !args[0]->ToInteger(ret->s8_)){
        RUNTIME_ERR(lineno,"invalid conversion to S8");
    }
    return ret;
}

__ValuePtr EvaluateU16(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = DT_U16;
    if(!args.empty() && !args[0]->ToInteger(ret->u16_)){
        RUNTIME_ERR(lineno,"invalid conversion to U16");
    }
    return ret;
}

__ValuePtr EvaluateS16(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = DT_S16;
    if(!args.empty() && !args[0]->ToInteger(ret->s16_)){
        RUNTIME_ERR(lineno,"invalid conversion to S16");
    }
    return ret;
}

__ValuePtr EvaluateU32(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = DT_U32;
    if(!args.empty() && !args[0]->ToInteger(ret->u32_)){
        RUNTIME_ERR(lineno,"invalid conversion to U32");
    }
    return ret;
}

__ValuePtr EvaluateS32(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = DT_S32;
    if(!args.empty() && !args[0]->ToInteger(ret->s32_)){
        RUNTIME_ERR(lineno,"invalid conversion to S32");
    }
    return ret;
}


__ValuePtr EvaluateU64(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = DT_U64;
    if(!args.empty() && !args[0]->ToInteger(ret->u64_)){
        RUNTIME_ERR(lineno,"invalid conversion to U64");
    }
    return ret;
}

__ValuePtr EvaluateS64(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = DT_S64;
    if(!args.empty() && !args[0]->ToInteger(ret->s64_)){
        RUNTIME_ERR(lineno,"invalid conversion to S64");
    }
    return ret;
}

__ValuePtr EvaluateSTR(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = DT_STR;
    if(!args.empty()){
        if(!args[0]->IsStrOrPA()){
            RUNTIME_ERR(lineno,"invalid conversion to STR");
        }else
            ret->str_ = args[0]->str_;
    }
    return ret;
}
__ValuePtr EvaluateRAW(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = DT_RAW;
    if(!args.empty()){
        if(!args[0]->IsStrOrPA()){
            RUNTIME_ERR(lineno,"invalid conversion to RAW");
        }else
            ret->str_ = args[0]->str_;
    }
    return ret;
}

__ValuePtr EvaluateTCP(const std::vector<__ValuePtr> & args,int lineno)
{
    if(args.size() == 1){
        if(args[0]->type_ == DT_TCP)
            return args[0];
        RUNTIME_ERR(lineno,"invalid conversion to TCP");
    }else if(args.size() >= 2){
        assert(args[0]->IsStrOrPA());
        const std::string ip = args[0]->str_;
        DBG_RT("remote ip="<<ip);
        CSockAddr addr;
        if(args[1]->IsIntOrPA()){
            int port = -1;
            if(!args[1]->ToInteger(port)){
                RUNTIME_ERR(lineno,"remote port error");
                return 0;
            }
            DBG_RT("remote port="<<port);
            addr.SetAddr(ip,port);
        }else if(args[1]->IsStrOrPA()){
            DBG_RT("remote port="<<args[1]->str_);
            addr.SetAddr(ip,args[1]->str_);
        }else{
            RUNTIME_ERR(lineno,"invalid port");
            return 0;
        }
        if(!addr.IsValid()){
            RUNTIME_ERR(lineno,"invalid ip or port,"<<CSockAddr::ErrMsg());
            return 0;
        }
        DBG_RT("remote addr="<<addr.ToString());
        __ValuePtr ret = New<CValue>();
        ret->type_ = DT_TCP;
        ret->tcp_ = New<CTcp>(lineno);
        if(args.size() == 3 && !args[2]->ToInteger(ret->tcp_->timeMs_)){
            RUNTIME_ERR(lineno,"invalid value for timeout(argutment 3)");
            return false;
        }
#if __REAL_CONNECT
        if(!ret->tcp_->Connect(addr)){
            RUNTIME_ERR(lineno,"cannot connect to remote address at "
                <<addr.ToString()<<","<<CSocket::ErrMsg());
            return 0;
        }
        if(ret->tcp_->timeMs_){
            if(!ret->tcp_->SetSendTimeout(ret->tcp_->timeMs_)){
                RUNTIME_ERR(lineno,"cannot set send timeout,"<<CSocket::ErrMsg());
                return 0;
            }
            if(!ret->tcp_->SetRecvTimeout(ret->tcp_->timeMs_)){
                RUNTIME_ERR(lineno,"cannot set recv timeout,"<<CSocket::ErrMsg());
                return 0;
            }
        }
#endif
        return ret;
    }
    return 0;
}
__ValuePtr EvaluateUDP(const std::vector<__ValuePtr> & args,int lineno)
{
    if(args.size() == 1){
        if(args[0]->type_ == DT_UDP)
            return args[0];
        RUNTIME_ERR(lineno,"invalid conversion to UDP");
    }else if(args.size() >= 2){
        assert(args[0]->IsStrOrPA());
        const std::string ip = args[0]->str_;
        DBG_RT("remote ip="<<ip);
        CSockAddr addr;
        if(args[1]->IsIntOrPA()){
            int port = -1;
            if(!args[1]->ToInteger(port)){
                RUNTIME_ERR(lineno,"remote port error");
                return 0;
            }
            DBG_RT("remote port="<<port);
            addr.SetAddr(ip,port);
        }else if(args[1]->IsStrOrPA()){
            DBG_RT("remote port="<<args[1]->str_);
            addr.SetAddr(ip,args[1]->str_);
        }else{
            RUNTIME_ERR(lineno,"invalid port");
            return 0;
        }
        if(!addr.IsValid()){
            RUNTIME_ERR(lineno,"invalid ip or port,"<<CSockAddr::ErrMsg());
            return 0;
        }
        DBG_RT("remote addr="<<addr.ToString());
        __ValuePtr ret = New<CValue>();
        ret->type_ = DT_UDP;
        ret->udp_ = New<CUdp>(lineno);
        if(args.size() == 3 && !args[2]->ToInteger(ret->udp_->timeMs_)){
            RUNTIME_ERR(lineno,"invalid value for timeout(argutment 3)");
            return false;
        }
#if __REAL_CONNECT
        if(!ret->udp_->Connect(addr)){
            RUNTIME_ERR(lineno,"cannot connect to remote address at "
                <<addr.ToString()<<","<<CSocket::ErrMsg());
            return 0;
        }
        if(ret->udp_->timeMs_){
            if(!ret->udp_->SetSendTimeout(ret->udp_->timeMs_)){
                RUNTIME_ERR(lineno,"cannot set send timeout,"<<CSocket::ErrMsg());
                return 0;
            }
            if(!ret->udp_->SetRecvTimeout(ret->udp_->timeMs_)){
                RUNTIME_ERR(lineno,"cannot set recv timeout,"<<CSocket::ErrMsg());
                return 0;
            }
        }
#endif
        return ret;
    }
    return 0;
}

__ValuePtr EvaluateHEX(const std::vector<__ValuePtr> & args,int lineno)
{
    assert(!args.empty());
    __ValuePtr ret = New<CValue>();
    ret->type_ = DT_STR;
    if(!args[0]->IsStrOrPA()){
        RUNTIME_ERR(lineno,"invalid conversion to string");
    }else
        ret->str_ = DumpHex(args[0]->str_,' ',false);
    return ret;
}
__ValuePtr EvaluateUNHEX(const std::vector<__ValuePtr> & args,int lineno)
{
    assert(!args.empty());
    __ValuePtr ret = New<CValue>();
    ret->type_ = DT_STR;
    if(!args[0]->IsStrOrPA()){
        RUNTIME_ERR(lineno,"invalid conversion to string");
    }else
        ret->str_ = UnHex(args[0]->str_);
    return ret;
}

static __ValuePtr __EvaluateIP(const std::vector<__ValuePtr> & args,int lineno,bool hbo)
{
    assert(!args.empty());
    __ValuePtr ret = New<CValue>();
    if(args[0]->IsInteger()){   //这里优先照顾STR
        U32 ip = 0;
        if(!args[0]->ToInteger(ip)){
            RUNTIME_ERR(lineno,"invalid conversion to U32");
            return 0;
        }
        ret->type_ = DT_STR;    //STR
        ret->str_ = IPv4String(ip,hbo);
    }else if(args[0]->IsStrOrPA()){
        ret->type_ = DT_U32;     //U32
        ret->u32_ = IPv4FromStr(args[0]->str_,hbo);
    }
    return ret;
}

__ValuePtr EvaluateIPN(const std::vector<__ValuePtr> & args,int lineno)
{
    return __EvaluateIP(args,lineno,false);
}

__ValuePtr EvaluateIPH(const std::vector<__ValuePtr> & args,int lineno)
{
    return __EvaluateIP(args,lineno,true);
}

void InvokeBO(bool net_bo,CSharedPtr<CCmd> cmd)
{
    runtime().SetByteOrder(net_bo);
    if(cmd)
        cmd->SetByteOrder(net_bo);
}

void InvokeSendRecv(bool is_send,CSharedPtr<CArgList> args,int lineno,CSharedPtr<CCmd> cmd)
{
    assert(cmd);
    if(is_send){
        assert(cmd->IsSend());
    }else{
        assert(cmd->IsRecv());
    }
    if(!args || args->args_.empty()){
        if(!runtime().default_conn_){
            RUNTIME_ERR(lineno,"no default connection");
        }else
            cmd->AddConnection(runtime().default_conn_,lineno);
    }else{
        for(size_t i = 0;i < args->args_.size();++i){
            assert((*args)[i]->var_);  //MUST be variable
            const std::string & vname = (*args)[i]->var_->varname_;
            CSharedPtr<CDeclare> decl = runtime().FindVar(vname); //connectin is global
            if(!decl){
                RUNTIME_ERR(lineno,"no symbol '"<<CRuntime::RealVarname(vname)
                    <<"' found");
                return;
            }
            if(!decl->val_){
                RUNTIME_ERR(lineno,"symbol '"<<CRuntime::RealVarname(vname)
                    <<"' is not initialized");
                return;
            }
            cmd->AddConnection(decl->val_,lineno);
        }
    }
}

void InvokeBeginEnd(bool is_begin,CSharedPtr<CArgList> args,int lineno,CSharedPtr<CCmd> cmd)
{
    assert(cmd && args);
    for(size_t i = 0;i < args->args_.size();++i){
        if(!(*args)[i])
            continue;
        assert((*args)[i]->IsVar());  //MUST be variable
        const std::string & vname = (*args)[i]->var_->varname_;
        if(is_begin && (*args)[i]->var_->begin_ != -1){
            RUNTIME_ERR(lineno,"cannot BEGIN '"<<CRuntime::RealVarname(vname)<<"' again");
            continue;
        }else if(!is_begin && (*args)[i]->var_->begin_ < 0){
            RUNTIME_ERR(lineno,"END '"<<CRuntime::RealVarname(vname)<<"' before BEGIN");
            continue;
        }
        CSharedPtr<CDeclare> decl = runtime().FindVar(vname,cmd);
        if(!decl){
            RUNTIME_ERR(lineno,"no symbol '"<<CRuntime::RealVarname(vname)<<"' found");
            continue;
        }
        if(decl->expr_){
            RUNTIME_ERR(lineno,"variable '"<<CRuntime::RealVarname(vname)
                <<"' is evaluated by expression, see LINE:"<<(*args)[i]->var_->lineno_);
            continue;
        }else if(!decl->IsSimplePost()){
            GAMMAR_ERR(lineno,"invalid variable for BEGIN or END function, see LINE:"
                <<decl->lineno_);
            continue;
        }
        if(is_begin){   //BEGIN
            (*args)[i]->var_->begin_ = cmd->SendDataOffset();
            cmd->Begin((*args)[i]);
        }else{          //END
            assert(decl->val_);
            size_t dis = cmd->SendDataOffset() - decl->var_->begin_;
            decl->var_->begin_ = -2;
            if(!decl->val_->FromInteger(dis)){
                RUNTIME_ERR(lineno,"variable '"<<CRuntime::RealVarname(vname)
                    <<"' is too small to hold offset("<<dis<<")");
            }else if(!decl->is_def_ && !cmd->PostPutValue(decl->val_,decl->offset_)){
                INTERNAL_ERR("cannot post pack '"<<CRuntime::RealVarname(vname)<<"'");
            }
            if(args != cmd->begin_list_)    //命令结束时会对所有BEGIN变量自动调用END，此时(args == cmd->begin_list_)
                cmd->End((*args)[i]);
        }
    }
}

void InvokeFUN(CSharedPtr<CArgList> args,int lineno,CSharedPtr<CCmd> cmd)
{
    assert(args && cmd);
    assert(!args->args_.empty() && (*args)[0]);
    CExpr & exp = *(*args)[0];
    assert(exp.IsVar());
    const std::string & fun_name = exp.var_->varname_;
    const CGlobal::__FunNode * fn = global().FindFunc(fun_name);
    if(!fn){
        RUNTIME_ERR(lineno,"cannot find function '"<<fun_name<<"'");
    }else{
        assert(fn->func_ && fn->dst_len_max_);
        size_t sz = 0;
        if(args->args_.size() > 1){
            CSharedPtr<CValue> v = (*args)[1]->Evaluate();
            if(!v){
                RUNTIME_ERR(lineno,"cannot evaluate parameter 2");
                return;
            }
            if(!v->ToInteger(sz)){
                RUNTIME_ERR(lineno,"argument 2 type mismatch");
                return;
            }
        }
        cmd->InvokeFun(fn->func_,fn->dst_len_max_,sz,lineno,fun_name);
    }
}

void InvokePrint(CSharedPtr<CArgList> args,int lineno)
{
    assert(args);
    std::ostringstream oss;
    for(size_t i = 0;i < args->args_.size();++i){
        CSharedPtr<CExpr> expr = (*args)[i];
        assert(expr);
        CSharedPtr<CValue> v = expr->Evaluate();
        if(v)
            oss<<v->ShowValue(false);
    }
    SHOW(oss.str());
}

void InvokeArray(bool is_start,CSharedPtr<CArgList> args,int lineno,CSharedPtr<CCmd> cmd)
{
    assert(cmd);
    if(!is_start)
        return cmd->EndArray(lineno);
    if(!args || args->args_.empty()){
        cmd->StartArray(lineno);
    }else{
        CSharedPtr<CExpr> expr = (*args)[0];
        assert(expr);
        CSharedPtr<CValue> v = expr->Evaluate();
        if(!v){
            RUNTIME_ERR(expr->lineno_,"cannot evaluate expression");
            return;
        }
        size_t sz = 0;
        if(!v->ToInteger(sz)){
            RUNTIME_ERR(lineno,"invalid conversion to array size(size_t)");
            return;
        }
        cmd->StartArray(sz,lineno);
    }
}

void InvokeSleep(CSharedPtr<CArgList> args,int lineno)
{
    assert(args && args->args_.size() == 1);
    CSharedPtr<CExpr> expr = (*args)[0];
    assert(expr);
    CSharedPtr<CValue> v = expr->Evaluate();
    if(!v){
        RUNTIME_ERR(expr->lineno_,"cannot evaluate parameter 1");
        return;
    }
    int sec = 0;
    if(!v->ToInteger(sec)){
        RUNTIME_ERR(expr->lineno_,"invalid value for parameter 1");
        return;
    }
    sleep(sec);
}
