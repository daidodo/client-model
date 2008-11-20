#ifndef DOZERG_ERROR_H_20081112
#define DOZERG_ERROR_H_20081112

#include <sstream>

void yyerror(const std::string & msg);

void grammar_error(int lineno,const std::string & msg);

void runtime_error(const std::string & msg);

#define SYNTAX_ERR(msg)     {std::ostringstream oss;oss<<msg;yyerror(oss.str().c_str());}

#define GAMMAR_ERR(ln,msg)  {std::ostringstream oss;oss<<msg;grammar_error(ln,oss.str());}

#define RUNTIME_ERR(msg)    {std::ostringstream oss;oss<<msg;runtime_error(oss.str());}

#endif
