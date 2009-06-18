#include "tokens.h"
#include "functions.h"
#include "y.tab.h"

bool IsBinaryPredict(int op_token){
    return (
        op_token == OP_LG ||
        op_token == OP_SM ||
        op_token == OP_LEQ ||
        op_token == OP_SEQ ||
        op_token == OP_EQ ||
        op_token == OP_NEQ
        );
}

bool IsUnaryPredict(int op_token){
    return (op_token == OP_NOT);
}

bool IsGlobalOnlyToken(int type_token)
{
    return IsConnectionToken(type_token)
        || type_token == __DEBUG;
}

bool IsLocalOnlyToken(int type_token)
{
    return (type_token == SEND || type_token == RECV
        || type_token == BEGIN_ || type_token == END
        || type_token == ARRAY || type_token == __END_ARRAY
        || type_token == FUN);
}

bool IsConnectionToken(int type_token)
{
    return (type_token == TCP || type_token == UDP);
}

bool IsRawToken(int type_token)
{
    return type_token == RAW;
}

bool CannotBeArray(int type_token)
{
    return (type_token == TCP || type_token == UDP || type_token == RAW);
}

bool IsFunToken(int fun_token)
{
    return (fun_token == FUN);
}

int FunRetType(int fun_token,const std::vector<int> * types)
{
    switch(fun_token){
        case HBO:case NBO:
        case SEND:case RECV:
        case BEGIN_:case END:
        case FUN:case PRINT:
        case ARRAY:case __END_ARRAY:
        case SLEEP:case __DEBUG:
            return DT_VOID;
        case TP_U8:
            return DT_U8;
        case TP_S8:
            return DT_S8;
        case TP_U16:
            return DT_U16;
        case TP_S16:
            return DT_S16;
        case TP_U32:
            return DT_U32;
        case TP_S32:
            return DT_S32;
        case TP_U64:
            return DT_U64;
        case TP_S64:
            return DT_S64;
        case STR:
        case HEX:case UNHEX:
            return DT_STR;
        case RAW:
            return DT_RAW;
        case TCP:
            return DT_TCP;
        case UDP:
            return DT_UDP;
        case __IPN:case __IPH:
            assert(types && !types->empty());
            return (DT_IsString((*types)[0]) ? DT_U32 : DT_STR);
    }
    return DT_NONE;
}

size_t FunArgCheck(int fun_token,const std::vector<int> & types,CSharedPtr<CArgList> arglist)
{
    assert((arglist && types.size() == arglist->args_.size()) || (!arglist && types.empty()));
    switch(fun_token){
        case HBO:case NBO:{         //no args
            if(!types.empty())
                return 1;
            break;}
        case TP_U8:case TP_S8:
        case TP_U16:case TP_S16:
        case TP_U32:case TP_S32:
        case TP_U64:case TP_S64:
        case __DEBUG:{   //integer
            if(types.size() == 1 && !DT_IsIntOrPA(types[0]))
                return 1;
            else if(types.size() > 1)
                return 2;
            break;}
        case STR:case RAW:{         //string
            if(types.size() == 1 && !DT_IsStrOrPA(types[0]))
                return 1;
            else if(types.size() > 1)
                return 2;
            break;}
        case TCP:case UDP:{         //(string + (string or interger)) or (UDP xor TCP)
            if(types.empty())
                return 1;
            else if(types.size() == 1){
                if(fun_token == TCP){
                    if(!DT_IsTcp(types[0]))
                        return 1;
                }else{
                    if(!DT_IsUdp(types[0]))
                        return 1;
                }
            }else if(types.size() <= 3){
                if(!DT_IsStrOrPA(types[0]))
                    return 1;
                if(!DT_IsIntOrPA(types[1]) &&  //integer
                    !DT_IsStrOrPA(types[1]))    //string
                    return 2;
                if(types.size() == 3 && !DT_IsIntOrPA(types[2]))   //integer
                    return 3;
            }else
                return 4;
            break;}
        case SEND:case RECV:{       //CValue::tcp_ or CValue::udp_
            for(size_t i = 0;i < types.size();++i)
                if(!((*arglist)[i]->IsVar() && DT_IsConnection(types[i])))
                    return (i + 1);
            break;}
        case HEX:case UNHEX:{       //string
            if(types.empty() || !DT_IsStrOrPA(types[0]))
                return 1;
            else if(types.size() > 1)
                return 2;
            break;}
        case FUN:{                  //VAR or VAR + integer
            if(types.empty() || !(*arglist)[0]->IsVar())
                return 1;
            else if(types.size() == 2 && !DT_IsIntOrPA(types[1]))
                return 2;
            else if(types.size() > 2)
                return 3;
            break;}
        case BEGIN_:case END:{
            if(types.empty())
                return 1;
            for(size_t i = 0;i < types.size();++i)
                if(!((*arglist)[i]->IsVar() && DT_IsInteger(types[i])))
                    return (i + 1);
            break;}
        case PRINT:{
            if(types.empty())
                return 1;
            for(size_t i = 0;i < types.size();++i)
                if(DT_IsVoid(types[i]))
                    return (i + 1);
            break;}
        case __IPN:case __IPH:{       //string or integer
            if(types.empty() || (!DT_IsStrOrPA(types[0]) && !DT_IsIntOrPA(types[0])))
                return 1;
            if(types.size() > 1)
                return 2;
            break;}
        case ARRAY:{
            if(types.size() == 1 && !DT_IsIntOrPA(types[0]))
                return 1;
            else if(types.size() > 1)
                return 2;
            break;}
        case __END_ARRAY:{
            if(!types.empty())
                return 1;
            break;}
        case SLEEP:{
            if(types.empty() || !DT_IsIntOrPA(types[0]))
                return 1;
            else if(types.size() > 1)
                return 2;
            break;}
    }
    return 0;
}

size_t OpArgTypeCheck(int op_token,int type1,int type2)
{
    switch(op_token){
        case OP_EQ:
            if(DT_IsString(type1)){
                if(!DT_IsString(type2))
                    return 2;
                break;
            }
        case OP_LG:case OP_SM:
        case OP_LEQ:case OP_SEQ:
        case OP_NEQ:
            if(DT_IsInteger(type1)){
                if(!DT_IsInteger(type2))
                    return 2;
            }else
                return 1;
            break;
        case OP_NOT:
            if(!DT_IsInteger(type1))
                return 1;
            break;
    }
    return 0;
}

int IsArrayBeginEndToken(int fun_token)
{
    return (fun_token == ARRAY ? 1 : (fun_token == __END_ARRAY ? 2 : 0));
}

int IsSendRecvToken(int fun_token)
{
    return (fun_token == SEND ? 1 : (fun_token == RECV ? 2 : 0));
}

bool IsStreamInToken(int op_token)
{
    return op_token == OP_IN;
}

bool IsStreamOutToken(int op_token)
{
    return op_token == OP_OUT;
}

CSharedPtr<CValue> FunEvaluate(int fun_token,const std::vector<CSharedPtr<CValue> > & args,int lineno)
{
    switch(fun_token){
        case TP_U8:
            return EvaluateU8(args,lineno);
        case TP_S8:
            return EvaluateS8(args,lineno);
        case TP_U16:
            return EvaluateU16(args,lineno);
        case TP_S16:
            return EvaluateS16(args,lineno);
        case TP_U32:
            return EvaluateU32(args,lineno);
        case TP_S32:
            return EvaluateS32(args,lineno);
        case TP_U64:
            return EvaluateU64(args,lineno);
        case TP_S64:
            return EvaluateS64(args,lineno);
        case STR:
            return EvaluateSTR(args,lineno);
        case RAW:
            return EvaluateRAW(args,lineno);
        case TCP:
            return EvaluateTCP(args,lineno);
        case UDP:
            return EvaluateUDP(args,lineno);
        case HEX:
            return EvaluateHEX(args,lineno);
        case UNHEX:
            return EvaluateUNHEX(args,lineno);
        case __IPN:
            return EvaluateIPN(args,lineno);
        case __IPH:
            return EvaluateIPH(args,lineno);
    }
    return 0;
}

void FunInvoke(int fun_token,CSharedPtr<CArgList> args,int lineno,CSharedPtr<CCmd> cmd)
{
    switch(fun_token){
        case HBO:case NBO:
            InvokeBO((fun_token == NBO),cmd);
            break;
        case SEND:case RECV:
            InvokeSendRecv((fun_token == SEND),args,lineno,cmd);
            break;
        case BEGIN_:case END:
            InvokeBeginEnd((fun_token == BEGIN_),args,lineno,cmd);
            break;
        case FUN:
            InvokeFUN(args,lineno,cmd);
            break;
        case PRINT:
            InvokePrint(args,lineno);
            break;
        case ARRAY:case __END_ARRAY:
            InvokeArray((fun_token == ARRAY),args,lineno,cmd);
            break;
        case SLEEP:
            InvokeSleep(args,lineno);
        case __DEBUG:
            InvokeDebug(args,lineno);
    }
}

int FunAssert(int op_token,CSharedPtr<CValue> v1,CSharedPtr<CValue> v2)
{
    assert(v1);
    switch(op_token){
        case OP_LG:assert(v2);return *v1 > *v2;
        case OP_SM:assert(v2);return *v1 < *v2;
        case OP_LEQ:assert(v2);return *v1 >= *v2;
        case OP_SEQ:assert(v2);return *v1 <= *v2;
        case OP_EQ:assert(v2);return *v1 == *v2;
        case OP_NEQ:assert(v2);return *v1 != *v2;
        case OP_NOT:assert(!v2);return !*v1;
    }
    return RET_OP_ERROR;
}
