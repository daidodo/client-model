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
    return IsConnectionToken(type_token);
}

bool IsLocalOnlyToken(int type_token)
{
    return (type_token == SEND || type_token == RECV
        || type_token == BEGIN_ || type_token == END
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

bool FunNeedNotCheckDefine(int fun_token)
{
    return (fun_token == FUN);
}

bool FunArgNumCheck(int fun_token,size_t argn)
{
    switch(fun_token){
        case HBO:case NBO:
            return argn == 0;
        case TP_U8:case TP_S8:
        case TP_U16:case TP_S16:
        case TP_U32:case TP_S32:
        case TP_U64:case TP_S64:
        case STR:case RAW:
        case SEND:case RECV:
            return argn <= 1;
            return true;
        case HEX:case UNHEX:
            return argn == 1;
        case TCP:case UDP:
            return argn >= 1 && argn <= 3;
        case FUN:
            return argn == 1 || argn == 2;
        case BEGIN_:case END:
            return argn > 0;
    }
    return false;
}

int FunRetType(int fun_token)
{
    switch(fun_token){
        case HBO:case NBO:
        case SEND:case RECV:
        case BEGIN_:case END:
        case FUN:
            return 0;   //void
        case TP_U8:
            return 3;   //CValue::u8_
        case TP_S8:
            return 4;   //CValue::s8_
        case TP_U16:
            return 5;   //CValue::u16_
        case TP_S16:
            return 6;   //CValue::s16_
        case TP_U32:
            return 7;   //CValue::u32_
        case TP_S32:
            return 8;   //CValue::s32_
        case TP_U64:
            return 9;   //CValue::u64_
        case TP_S64:
            return 10;  //CValue::s64_
        case STR:
        case HEX:case UNHEX:
            return 11;  //CValue::str_
        case RAW:
            return 14;  //CValue::str_
        case TCP:
            return 12;  //CValue::tcp_
        case UDP:
            return 13;  //CValue::udp_
    }
    return -1;
}

size_t FunArgTypeCheck(int fun_token,std::vector<int> & types,CSharedPtr<CArgList> arglist)
{
    switch(fun_token){
        case HBO:case NBO:{         //no args
            if(!types.empty())
                return 1;
            break;}
        case TP_U8:case TP_S8:
        case TP_U16:case TP_S16:
        case TP_U32:case TP_S32:
        case TP_U64:case TP_S64:{   //integer
            if(!types.empty() && !CValue::IsInteger(types[0]))
                return 1;
            break;}
        case STR:case RAW:{         //string
            if(!types.empty() && !CValue::IsString(types[0]))
                return 1;
            break;}
        case TCP:case UDP:{         //(string + (string or interger)) or (UDP xor TCP)
            if(types.empty())
                return 1;
            else if(types.size() == 1){
                if(fun_token == TCP){
                    if(!CValue::IsTcp(types[0]))
                        return 1;
                }else{
                    if(!CValue::IsUdp(types[0]))
                        return 1;
                }
            }else if(types.size() <= 3){
                if(!CValue::IsString(types[0]))
                    return 1;
                if(!CValue::IsInteger(types[1]) &&  //integer
                    !CValue::IsString(types[1]))    //string
                    return 2;
                if(types.size() == 3 && !CValue::IsInteger(types[2]))   //integer
                    return 3;
            }else
                return 4;
            break;}
        case SEND:case RECV:{       //CValue::tcp_ or CValue::udp_
            if(arglist){
                for(size_t i = 0;i < types.size();++i)
                    if(!(*arglist)[i]->IsVar() || !CValue::IsConnection(types[i]))
                        return (i + 1);
            }
            break;}
        case HEX:case UNHEX:{       //string
            if(types.empty() || !CValue::IsString(types[0]))
                return 1;
            break;}
        case FUN:{                  //VAR or VAR + integer
            if(types.empty() || !(*arglist)[0]->IsVar())
                return 1;
            else if(types.size() == 2 && !CValue::IsInteger(types[1]))
                return 2;
            else if(types.size() > 2)
                return 3;
            break;}
        case BEGIN_:case END:{
            assert(arglist);
            for(size_t i = 0;i < types.size();++i)
                if(!(*arglist)[i]->IsVar() || !CValue::IsInteger(types[i]))
                    return (i + 1);
            break;}
    }
    return 0;
}

size_t OpArgTypeCheck(int op_token,int type1,int type2)
{
    switch(op_token){
        case OP_EQ:
            if(CValue::IsString(type1)){
                if(!CValue::IsString(type2))
                    return 2;
                break;
            }
        case OP_LG:case OP_SM:
        case OP_LEQ:case OP_SEQ:
        case OP_NEQ:
            if(CValue::IsInteger(type1)){
                if(!CValue::IsInteger(type2))
                    return 2;
            }else
                return 1;
            break;
        case OP_NOT:
            if(!CValue::IsInteger(type1))
                return 1;
            if(type2)
                return 2;
            break;
    }
    return 0;
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
    return -3;
}
