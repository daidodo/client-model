#include <iostream>
#include "errors.h"
#include "global.h"

void yyerror(const char * msg){
    std::cerr<<global().input_file<<":"<<global().lineno<<" : '"
        <<global().cur_tok<<"' "<<msg<<std::endl;
    exit(1);
}

void gmm_error(const std::string & msg)
{
    std::cerr<<global().input_file<<":"<<global().lineno<<" : "
        <<msg<<std::endl;
}
