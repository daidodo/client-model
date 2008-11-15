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

bool FunNotNeedCheckkDefine(int fun_token)
{
    return (fun_token == FUN);
}
