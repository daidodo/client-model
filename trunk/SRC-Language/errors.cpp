#include <iostream>
#include "errors.h"
#include "global.h"

void yyerror(const std::string & msg){
    std::cerr<<global().input_file<<":"<<global().lineno<<" - '"
        <<global().cur_tok<<"' "<<msg<<std::endl;
    exit(1);
}

void gmm_error(int lineno,const std::string & msg)
{
    std::cerr<<global().input_file<<":"<<lineno<<" - "
        <<msg<<std::endl;
    exit(1);
}
