#ifndef DOZERG_ERROR_H_20081112
#define DOZERG_ERROR_H_20081112

#include <sstream>

void yyerror(const std::string & msg);

void grammar_error(int lineno,const std::string & msg);

void runtime_error(int lineno,const std::string & msg);

void internal_error(const std::string & msg);

void assert_fail(int lineno,const std::string & msg);

#define SYNTAX_ERR(msg)         {std::ostringstream oss;oss<<msg;yyerror(oss.str().c_str());}

#define GAMMAR_ERR(ln,msg)      {std::ostringstream oss;oss<<msg;grammar_error(ln,oss.str());}

#define RUNTIME_ERR(ln,msg)     {std::ostringstream oss;oss<<msg;runtime_error(ln,oss.str());}

#define INTERNAL_ERR(msg)       {std::ostringstream oss;oss<<msg;internal_error(oss.str());}

#define ASSERT_FAIL(cmd,ln,msg) {cmd->DumpRecvData();std::ostringstream oss;oss<<msg;assert_fail(ln,oss.str());}

#endif
