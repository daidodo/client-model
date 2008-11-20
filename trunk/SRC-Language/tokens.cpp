#include "tokens.h"
#include "symbols.h"
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
        case HEX:case UNHEX:
            return argn == 1;
        case TCP:case UDP:
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
        case STR:case RAW:
        case HEX:case UNHEX:
            return 11;  //CValue::str_
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
            if(!types.empty() && !(types[0] > 0 && types[0] <= 10))
                return 1;
            break;}
        case STR:case RAW:{         //string
            if(!types.empty() && types[0] != 11)
                return 1;
            break;}
        case TCP:case UDP:{         //(string + (string or interger)) or (UDP xor TCP)
            if(types.empty())
                return 1;
            else if(types.size() == 1){
                if(fun_token == TCP){
                    if(types[0] != 12)
                        return 1;
                }else{
                    if(types[0] != 13)
                        return 1;
                }
            }else if(types.size() == 2){
                if(types[0] != 11)
                    return 1;
                if(!(types[1] > 0 && types[1] <= 11))
                    return 2;
            }else
                return 3;
            break;}
        case SEND:case RECV:{       //CValue::tcp_ or CValue::udp_
            if(arglist){
                for(size_t i = 0;i < types.size();++i)
                    if(!(*arglist)[i]->IsVar() || (types[0] != 12 && types[0] != 13))
                        return (i + 1);
            }
            break;}
        case HEX:case UNHEX:{       //string
            if(types.empty() || types[0] != 11)
                return 1;
            break;}
        case FUN:{                  //VAR or VAR + integer
            if(types.empty() || !(*arglist)[0]->IsVar())
                return 1;
            else if(types.size() == 2 && !(types[1] > 0 && types[1] <= 10))
                return 2;
            else if(types.size() > 2)
                return 3;
            break;}
        case BEGIN_:case END:{
            assert(arglist);
            for(size_t i = 0;i < types.size();++i)
                if(!(*arglist)[i]->IsVar() || !(types[i] > 0 && types[i] <= 10))
                    return (i + 1);
            break;}
    }
    return 0;
}

int IsSendRecvToken(int fun_token)
{
    return (fun_token == SEND ? 1 : (fun_token == RECV ? 2 : 0));
}

int IsStreamInToken(int op_token)
{
    return op_token == OP_IN;
}

int IsStreamOutToken(int op_token)
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

void FunInvoke(int fun_token,CSharedPtr<CArgList> args,int lineno_,CSharedPtr<CCmd> cmd)
{
    switch(fun_token){
        case HBO:case NBO:
            InvokeBO((fun_token == NBO),cmd);
            break;
        case SEND:case RECV:
            InvokeSendRecv((fun_token == SEND),args,lineno_,cmd);
            break;
        case BEGIN_:case END:
            InvokeBeginEnd((fun_token == BEGIN_),args,lineno_,cmd);
            break;
        case FUN:
            break;
    }
}
