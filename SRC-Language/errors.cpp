#include <iostream>
#include "config.h"
#include "errors.h"
#include "global.h"

void yyerror(const std::string & msg){
    std::cerr<<global().input_file<<":"<<global().lineno<<" - '"
        <<global().cur_tok<<"' "<<msg<<std::endl;
#if __SYN_ERR_EXIT
    exit(1);
#endif
}

void grammar_error(int lineno,const std::string & msg)
{
    std::cerr<<global().input_file<<":"<<lineno<<" - "
        <<msg<<std::endl;
#if __GMM_ERR_EXIT
    exit(1);
#endif
}
