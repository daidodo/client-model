#include <limits>
#include "global.h"
#include "mm.h"
#include "errors.h"
#include "util.h"
#include "functions.h"

//template<typename T>
//static void IntegerCtor(const std::vector<__ValuePtr> & args,int lineno,
//                              T & res,const char * type_str)
//{
//    assert(args.size() < 2);
//    if(args.empty())
//        return;
//    __ValuePtr arg = args[0];
//    const T MIN = std::numeric_limits<T>::min();
//    const T MAX = std::numeric_limits<T>::max();
//    switch(arg->type_){
//        case 1:{    //int_
//            if(arg->int_ < MIN || arg->int_ > MAX){
//                RUNTIME_ERR(lineno,"invalid value for "<<type_str);
//            }
//            res = arg->int_;
//            break;}
//        case 2:{    //long_
//            if(arg->long_ < MIN || arg->long_ > MAX){
//                RUNTIME_ERR(lineno,"invalid conversion from long to "<<type_str);
//            }
//            res = arg->long_;
//            break;}
//        case 3:{    //u8_
//            if(arg->u8_ < MIN || arg->u8_ > MAX){
//                RUNTIME_ERR(lineno,"invalid conversion from U8 to "<<type_str);
//            }
//            res = arg->u8_;
//            break;}
//        case 4:{    //s8_
//            if(arg->s8_ < MIN || arg->s8_ > MAX){
//                RUNTIME_ERR(lineno,"invalid conversion from S8 to "<<type_str);
//            }
//            res = arg->s8_;
//            break;}
//        case 5:{    //u16_
//            if(arg->u16_ < MIN || arg->u16_ > MAX){
//                RUNTIME_ERR(lineno,"invalid conversion from U16 to "<<type_str);
//            }
//            res = arg->u16_;
//            break;}
//        case 6:{    //s16_
//            if(arg->s16_ < MIN || arg->s16_ > MAX){
//                RUNTIME_ERR(lineno,"invalid conversion from U16 to "<<type_str);
//            }
//            res = arg->s16_;
//            break;}
//        case 7:{    //u32_
//            if(arg->u32_ < MIN || arg->u32_ > MAX){
//                RUNTIME_ERR(lineno,"invalid conversion from U16 to "<<type_str);
//            }
//            res = arg->u32_;
//            break;}
//        case 8:{    //s32_
//            break;}
//            if(arg->s32_ < MIN || arg->s32_ > MAX){
//                RUNTIME_ERR(lineno,"invalid conversion from U16 to "<<type_str);
//            }
//            res = arg->s32_;
//        case 9:{    //u64_
//            if(arg->u64_ < MIN || arg->u64_ > MAX){
//                RUNTIME_ERR(lineno,"invalid conversion from U16 to "<<type_str);
//            }
//            res = arg->u64_;
//            break;}
//        case 10:{   //s64_
//            if(arg->s64_ < MIN || arg->s64_ > MAX){
//                RUNTIME_ERR(lineno,"invalid conversion from U16 to "<<type_str);
//            }
//            res = arg->s64_;
//            break;}
//        default:{
//            RUNTIME_ERR(lineno,"invalid conversion to "<<type_str);
//        }
//    }
//}

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
        if(args[0]->type_ != 11){
            RUNTIME_ERR(lineno,"invalid conversion to STR");
        }else
            ret->str_ = args[0]->str_;
    }
    return ret;
}
__ValuePtr EvaluateRAW(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 11;
    if(!args.empty()){
        if(args[0]->type_ != 11){
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
    }else if(args.size() == 2){
        assert(args[0]->type_ == 11);   //string
        __ValuePtr ret = New<CValue>();
        ret->type_ = 12;
    //make tcp connection



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
        assert(args[0]->type_ == 11);   //string
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
        if(args[0]->type_ != 11){
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
        if(args[0]->type_ != 11){
            RUNTIME_ERR(lineno,"invalid conversion to RAW");
        }else
            ret->str_ = UnHex(args[0]->str_);
    }
    return ret;
}

void InvokeBO(bool net_bo,CSharedPtr<CCmd> cmd)
{
    runtime().SetByteOrder(net_bo);
    cmd->SetByteOrder(net_bo);
}

void InvokeSendRecv(bool is_send,CSharedPtr<CArgList> args,int lineno,CSharedPtr<CCmd> cmd)
{
    if(is_send){
        assert(cmd->IsSend());
    }else{
        assert(cmd->IsRecv());
    }
    if(!args || args->args_.empty()){
        if(!runtime().default_conn_){
            RUNTIME_ERR(lineno,"no default connection");
        }else
            cmd->AddConnection(runtime().default_conn_);
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
            cmd->AddConnection(decl->val_);
        }
    }
}

void InvokeBeginEnd(bool is_begin,CSharedPtr<CArgList> args,int lineno,CSharedPtr<CCmd> cmd)
{
    assert(cmd && args && !args->args_.empty());
    for(size_t i = 0;i < args->args_.size();++i){
        assert((*args)[i]->var_);  //MUST be variable
        if(is_begin && (*args)[i]->var_->begin_ != -1){
            RUNTIME_ERR(lineno,"cannot BEGIN '"<<(*args)[i]->var_->varname_<<"' again");
            return;
        }else if(!is_begin && (*args)[i]->var_->begin_ == -1){
            RUNTIME_ERR(lineno,"END '"<<(*args)[i]->var_->varname_<<"' before BEGIN");
            return;
        }
        CSharedPtr<CDeclare> decl = runtime().FindVar((*args)[i]->var_->varname_,cmd);
        if(!decl){
            RUNTIME_ERR(lineno,"no symbol '"<<(*args)[i]->var_->varname_<<"' found");
            return;
        }
        if(decl->expr_){
            RUNTIME_ERR(lineno,"variable '"<<(*args)[i]->var_->varname_
                <<"' is evaluated by expression, see LINE:"<<(*args)[i]->var_->lineno_);
            return;
        }
        if(is_begin){
            (*args)[i]->var_->begin_ = cmd->DataOffset();
        }else{  //END
            assert(decl->val_);
            decl->val_->FromInteger(cmd->DataOffset() - size_t(decl->var_->begin_));
        }


        //}else{  //END
        //    if((*args)[i]->var_->begin_ == -1){
        //        RUNTIME_ERR(lineno,"END '"<<(*args)[i]->var_->varname_<<"' before BEGIN");
        //        return;
        //    }
        //    CSharedPtr<CDeclare> decl = runtime().FindVar((*args)[i]->var_->varname_,cmd);
        //    if(!decl){
        //        RUNTIME_ERR(lineno,"no symbol '"<<(*args)[i]->var_->varname_<<"' found");
        //        return;
        //    }

        //    (*args)[i]->var_->end_ = cmd->DataOffset();
        //}
    }
}
