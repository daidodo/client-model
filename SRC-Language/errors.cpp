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

void runtime_error(int lineno,const std::string & msg)
{
    std::cerr<<global().input_file<<":"<<lineno<<" - (runtime)"
        <<msg<<std::endl;
    ERR_INCR;
}

void internal_error(const std::string & msg)
{
    std::cerr<<"(internal error) - "<<msg<<std::endl;
    ERR_INCR;
    throw 0;
}

void assert_fail(int lineno,const std::string & msg)
{
    std::cerr<<global().input_file<<":"<<lineno<<" - (assertion failed)"
        <<msg<<std::endl;
    exit(1);
}
