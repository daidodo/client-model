#include <iostream>
#include "global.h"
#include "config.h"

void yyerror(const std::string & msg){
    std::cerr<<global().input_file<<":"<<LINE_NO<<" - '"
        <<CUR_TOK<<"' "<<msg<<std::endl;
    ERR_INCR;
}

void grammar_error(int lineno,const std::string & msg)
{
    std::cerr<<global().input_file<<":"<<lineno<<" - "
        <<msg<<std::endl;
    ERR_INCR;
}

