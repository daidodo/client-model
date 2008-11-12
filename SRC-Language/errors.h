#ifndef DOZERG_ERROR_H_20081112
#define DOZERG_ERROR_H_20081112

#include <sstream>

void yyerror(const char * msg);

void gmm_error(const std::string & msg);

#define LEX_ERROR(msg)  {std::ostringstream oss;oss<<msg;yyerror(oss.str().c_str());}

#define GMM_ERROR(msg)  {std::ostringstream oss;oss<<msg;gmm_error(oss.str());}

#endif
