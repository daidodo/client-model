#ifndef DOZERG_ERROR_H_20081112
#define DOZERG_ERROR_H_20081112

#include <sstream>

void yyerror(const std::string & msg);

void gmm_error(int lineno,const std::string & msg);

#define LEX_ERROR(msg)      {std::ostringstream oss;oss<<msg;yyerror(oss.str().c_str());}

#define GMM_ERROR(ln,msg)   {std::ostringstream oss;oss<<msg;gmm_error(ln,oss.str());}

#endif
