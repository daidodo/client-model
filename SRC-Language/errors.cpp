#include <iostream>
#include "global.h"
#include "config.h"
#include "errors.h"

void yyerror(const std::string & msg){
    std::cerr<<global().input_file<<":"<<LINE_NO<<" - '"
        <<CUR_TOK<<"' "<<msg<<std::endl;
#if __SYN_ERR_EXIT
    exit(1);
#endif
    ERR_INCR;
}

void grammar_error(int lineno,const std::string & msg)
{
    std::cerr<<global().input_file<<":"<<lineno<<" - "
        <<msg<<std::endl;
#if __GMM_ERR_EXIT
    exit(1);
#endif
    ERR_INCR;
}
