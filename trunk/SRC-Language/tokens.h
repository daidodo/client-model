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

bool IsRawToken(int type_token);

bool CannotBeArray(int type_token);

bool IsFunToken(int fun_token);

bool FunArgNumCheck(int fun_token,size_t argn);

int FunRetType(int fun_token,const std::vector<int> * types = 0);

size_t FunArgTypeCheck(int fun_token,const std::vector<int> & types,CSharedPtr<CArgList> arglist);

size_t OpArgTypeCheck(int op_token,int type1,int type2);

int IsSendRecvToken(int fun_token);

bool IsStreamInToken(int op_token);

bool IsStreamOutToken(int op_token);

CSharedPtr<CValue> FunEvaluate(int fun_token,const std::vector<CSharedPtr<CValue> > & args,int lineno);

void FunInvoke(int fun_token,CSharedPtr<CArgList> args,int lineno,CSharedPtr<CCmdStruct> cmd);

int FunAssert(int op_token,CSharedPtr<CValue> v1,CSharedPtr<CValue> v2);

#endif
