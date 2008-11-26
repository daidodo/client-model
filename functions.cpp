#include <limits>
#include "global.h"
#include "mm.h"
#include "errors.h"
#include "util.h"
#include "dbg.h"
#include "functions.h"

__ValuePtr EvaluateU8(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 3;
    if(!args.empty() && !args[0]->ToInteger(ret->u8_)){
        RUNTIME_ERR(lineno,"invalid conversion to U8");
    }
    return ret;
}

__ValuePtr EvaluateS8(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 4;
    if(!args.empty() && !args[0]->ToInteger(ret->s8_)){
        RUNTIME_ERR(lineno,"invalid conversion to S8");
    }
    return ret;
}

__ValuePtr EvaluateU16(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 5;
    if(!args.empty() && !args[0]->ToInteger(ret->u16_)){
        RUNTIME_ERR(lineno,"invalid conversion to U16");
    }
    return ret;
}

__ValuePtr EvaluateS16(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 6;
    if(!args.empty() && !args[0]->ToInteger(ret->s16_)){
        RUNTIME_ERR(lineno,"invalid conversion to S16");
    }
    return ret;
}

__ValuePtr EvaluateU32(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 7;
    if(!args.empty() && !args[0]->ToInteger(ret->u32_)){
        RUNTIME_ERR(lineno,"invalid conversion to U32");
    }
    return ret;
}

__ValuePtr EvaluateS32(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 8;
    if(!args.empty() && !args[0]->ToInteger(ret->s32_)){
        RUNTIME_ERR(lineno,"invalid conversion to S32");
    }
    return ret;
}


__ValuePtr EvaluateU64(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 9;
    if(!args.empty() && !args[0]->ToInteger(ret->u64_)){
        RUNTIME_ERR(lineno,"invalid conversion to U64");
    }
    return ret;
}

__ValuePtr EvaluateS64(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 10;
    if(!args.empty() && !args[0]->ToInteger(ret->s64_)){
        RUNTIME_ERR(lineno,"invalid conversion to S64");
    }
    return ret;
}

__ValuePtr EvaluateSTR(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 11;
    if(!args.empty()){
        if(!args[0]->IsString()){
            RUNTIME_ERR(lineno,"invalid conversion to STR");
        }else
            ret->str_ = args[0]->str_;
    }
    return ret;
}
__ValuePtr EvaluateRAW(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 14;
    if(!args.empty()){
        if(!args[0]->IsString()){
            RUNTIME_ERR(lineno,"invalid conversion to RAW");
        }else
            ret->str_ = args[0]->str_;
    }
    return ret;
}

__ValuePtr EvaluateTCP(const std::vector<__ValuePtr> & args,int lineno)
{
    if(args.size() == 1){
        if(args[0]->type_ == 12)
            return args[0];
        RUNTIME_ERR(lineno,"invalid conversion to TCP");
    }else if(args.size() >= 2){
        assert(args[0]->IsString());
        const std::string ip = args[0]->str_;
        DBG_RT("remote ip="<<ip);
        CSockAddr addr;
        if(args[1]->IsInteger()){
            int port = -1;
            if(!args[1]->ToInteger(port)){
                RUNTIME_ERR(lineno,"remote port error");
                return 0;
            }
            DBG_RT("remote port="<<port);
            addr.SetAddr(ip,port);
        }else if(args[1]->IsString()){
            DBG_RT("remote port="<<args[1]->str_);
            addr.SetAddr(ip,args[1]->str_);
        }else{
            RUNTIME_ERR(lineno,"invalid conversion to int");
            return 0;
        }
        if(!addr.IsValid()){
            RUNTIME_ERR(lineno,"invalid ip or port,"<<CSockAddr::ErrMsg());
            return 0;
        }
        DBG_RT("remote addr="<<addr.ToString());
        __ValuePtr ret = New<CValue>();
        ret->type_ = 12;
        ret->tcp_ = New<CTcp>(lineno);
        if(args.size() == 3){
            U32 timeS = 0;
            if(!args[2]->ToInteger(ret->tcp_->timeMs_)){
                RUNTIME_ERR(lineno,"invalid argument 3 for timeout value");
                return false;
            }
        }
#if __REAL_CONNECT
        if(!ret->tcp_->Connect(addr)){
            RUNTIME_ERR(lineno,"cannot connect to remote address,"<<CSocket::ErrMsg());
            return 0;
        }
        //if(!ret->tcp_->SetBlock(false)){
        //    RUNTIME_ERR(lineno,"set nonblock error,"<<CSocket::ErrMsg());
        //    return 0;
        //}
#endif
        return ret;
    }
    return 0;
}
__ValuePtr EvaluateUDP(const std::vector<__ValuePtr> & args,int lineno)
{
    if(args.size() == 1){
        if(args[0]->type_ == 13)
            return args[0];
        RUNTIME_ERR(lineno,"invalid conversion to TCP");
    }else if(args.size() == 2){
        assert(args[0]->IsString());   //string
        __ValuePtr ret = New<CValue>();
        ret->type_ = 13;
    //make udp connection




        return ret;
    }
    return 0;
}

__ValuePtr EvaluateHEX(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 11;
    if(!args.empty()){
        if(!args[0]->IsString()){
            RUNTIME_ERR(lineno,"invalid conversion to RAW");
        }else
            ret->str_ = DumpHex(args[0]->str_);
    }
    return ret;
}
__ValuePtr EvaluateUNHEX(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 11;
    if(!args.empty()){
        if(!args[0]->IsString()){
            RUNTIME_ERR(lineno,"invalid conversion to RAW");
        }else
            ret->str_ = UnHex(args[0]->str_);
    }
    return ret;
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
            CSharedPtr<CDeclare> decl = runtime().FindVar((*args)[i]->var_->varname_); //connectin is global
            if(!decl){
                RUNTIME_ERR(lineno,"no symbol '"<<(*args)[i]->var_->varname_<<"' found");
                return;
            }
            if(!decl->val_){
                RUNTIME_ERR(lineno,"symbol '"<<(*args)[i]->var_->varname_
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
        assert((*args)[i]->var_);  //MUST be variable
        if(is_begin && (*args)[i]->var_->begin_ != -1){
            RUNTIME_ERR(lineno,"cannot BEGIN '"<<(*args)[i]->var_->varname_<<"' again");
            continue;
        }else if(!is_begin && (*args)[i]->var_->begin_ < 0){
            RUNTIME_ERR(lineno,"END '"<<(*args)[i]->var_->varname_<<"' before BEGIN");
            continue;
        }
        CSharedPtr<CDeclare> decl = runtime().FindVar((*args)[i]->var_->varname_,cmd);
        if(!decl){
            RUNTIME_ERR(lineno,"no symbol '"<<(*args)[i]->var_->varname_<<"' found");
            continue;
        }
        if(decl->expr_){
            RUNTIME_ERR(lineno,"variable '"<<(*args)[i]->var_->varname_
                <<"' is evaluated by expression, see LINE:"<<(*args)[i]->var_->lineno_);
            continue;
        }
        if(is_begin){
            (*args)[i]->var_->begin_ = cmd->SendDataOffset();
            cmd->Begin((*args)[i]);
        }else{  //END
            assert(decl->val_);
            size_t dis = cmd->SendDataOffset() - decl->var_->begin_;
            if(!decl->val_->FromInteger(dis)){
                RUNTIME_ERR(lineno,"variable '"<<(*args)[i]->var_->varname_
                    <<"' is too small to hold offset("<<dis<<")");
            }
            decl->var_->begin_ = -2;
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
    std::string fun_name = exp.var_->varname_;
    CGlobal::__Func fp = global().FindFunc(fun_name);
    if(!fp){
        RUNTIME_ERR(lineno,"cannot find function '"<<fun_name<<"'");
    }else{
        size_t sz = 0;
        if(args->args_.size() > 1){
            CSharedPtr<CValue> v = (*args)[1]->Evaluate();
            if(!v){
                RUNTIME_ERR(lineno,"cannot evaluate argument 2");
                return;
            }
            if(!v->ToInteger(sz)){
                RUNTIME_ERR(lineno,"argument 2 type mismatch");
                return;
            }
        }
        cmd->InvokeFun(fp,sz,lineno,fun_name);
    }
}
