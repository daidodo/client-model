#ifndef DOZERG_COMMON_H_20081112
#define DOZERG_COMMON_H_20081112

#include <cstddef>
#include <vector>
#include "symbols.h"

bool IsBinaryPredict(int op_token);

bool IsUnaryPredict(int op_token);

bool IsGlobalOnlyToken(int type_token);

bool IsLocalOnlyToken(int type_token);

bool IsConnectionToken(int type_token);

bool CannotBeArray(int type_token);

bool FunNeedNotCheckDefine(int fun_token);

bool FunArgNumCheck(int fun_token,size_t argn);

int FunRetType(int fun_token);

size_t FunArgTypeCheck(int fun_token,std::vector<int> & types);

CSharedPtr<CValue> FunEvaluate(int fun_token,const std::vector<CSharedPtr<CValue> > & args,int lineno);

#endif
