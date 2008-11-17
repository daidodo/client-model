#ifndef DOZERG_COMMON_H_20081112
#define DOZERG_COMMON_H_20081112

#include <cstddef>

bool IsBinaryPredict(int op_token);

bool IsUnaryPredict(int op_token);

bool IsOnlyGlobalType(int type_token);

bool CannotBeArray(int type_token);

bool FunNeedNotCheckDefine(int fun_token);

bool FunArgNumCheck(int fun_token,size_t argn);

#endif
