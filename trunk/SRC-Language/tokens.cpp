#include "tokens.h"
#include "symbols.h"
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

bool IsOnlyGlobalType(int type_token)
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
        case BEGIN_:case END:
            return true;
    }
    return false;
}
