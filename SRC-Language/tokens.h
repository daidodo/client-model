#ifndef DOZERG_COMMON_H_20081112
#define DOZERG_COMMON_H_20081112

bool IsBinaryPredict(int op_token);

bool IsUnaryPredict(int op_token);

bool IsOnlyGlobalType(int type_token);

bool CannotBeArray(int type_token);

bool FunNotNeedCheckkDefine(int fun_token);

#endif
