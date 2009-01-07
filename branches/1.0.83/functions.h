#ifndef DOZERG_FUNCTIONS_H_20081119
#define DOZERG_FUNCTIONS_H_20081119

#include <vector>
#include "symbols.h"
#include "common/SharedPtr.h"

typedef CSharedPtr<CValue> __ValuePtr;

//no side effects
__ValuePtr EvaluateU8(const std::vector<__ValuePtr> & args,int lineno);
__ValuePtr EvaluateS8(const std::vector<__ValuePtr> & args,int lineno);

__ValuePtr EvaluateU16(const std::vector<__ValuePtr> & args,int lineno);
__ValuePtr EvaluateS16(const std::vector<__ValuePtr> & args,int lineno);

__ValuePtr EvaluateU32(const std::vector<__ValuePtr> & args,int lineno);
__ValuePtr EvaluateS32(const std::vector<__ValuePtr> & args,int lineno);

__ValuePtr EvaluateU64(const std::vector<__ValuePtr> & args,int lineno);
__ValuePtr EvaluateS64(const std::vector<__ValuePtr> & args,int lineno);

__ValuePtr EvaluateSTR(const std::vector<__ValuePtr> & args,int lineno);
__ValuePtr EvaluateRAW(const std::vector<__ValuePtr> & args,int lineno);

__ValuePtr EvaluateTCP(const std::vector<__ValuePtr> & args,int lineno);
__ValuePtr EvaluateUDP(const std::vector<__ValuePtr> & args,int lineno);

__ValuePtr EvaluateHEX(const std::vector<__ValuePtr> & args,int lineno);
__ValuePtr EvaluateUNHEX(const std::vector<__ValuePtr> & args,int lineno);

__ValuePtr EvaluateIPN(const std::vector<__ValuePtr> & args,int lineno);
__ValuePtr EvaluateIPH(const std::vector<__ValuePtr> & args,int lineno);

//have side effects
void InvokeBO(bool net_bo,CSharedPtr<CCmd> cmd);

void InvokeSendRecv(bool is_send,CSharedPtr<CArgList> args,int lineno,CSharedPtr<CCmd> cmd);

void InvokeBeginEnd(bool is_begin,CSharedPtr<CArgList> args,int lineno,CSharedPtr<CCmd> cmd);

void InvokeFUN(CSharedPtr<CArgList> args,int lineno,CSharedPtr<CCmd> cmd);

void InvokePrint(CSharedPtr<CArgList> args,int lineno);

void InvokeArray(bool is_start,CSharedPtr<CArgList> args,int lineno,CSharedPtr<CCmd> cmd);

void InvokeSleep(CSharedPtr<CArgList> args,int lineno);

#endif
