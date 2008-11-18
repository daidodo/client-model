#include <cassert>
#include <iostream>
#include "global.h"
#include "errors.h"

extern FILE * yyin;

int yyparse();

void CGlobal::ErrFound(){
    if(++err_count_ > MAX_ERRORS)
        throw 0;
}

void CGlobal::Init(){
    lineno = 1;
    err_count_ = 0;
    cur_tok.clear();
    program_ = New<CProgram>();
}

bool CGlobal::Compile(const std::string & fname){
    if(!program_){
        std::cerr<<"compile environment not initialized!\n";
        return false;
    }
    yyin = fopen(fname.c_str(),"r");
    if(!yyin){
        std::cerr<<"cannot open file '"<<fname<<"'\n";
        return false;
    }
    input_file = fname;
    try{
        yyparse();
    }catch(int){}
    fclose(yyin);
    yyin = 0;
    if(err_count_){
        std::cerr<<"total "<<err_count_<<" error(s)\n";
        return false;
    }
    return true;
}

bool CGlobal::Build()
{
    if(!program_){
        std::cerr<<"program not ready!\n";
        return false;
    }
    runtime_ = New<CRuntime>();
    try{
        runtime_->Interpret(*program_);
    }catch(int){}
    if(err_count_){
        std::cerr<<"total "<<err_count_<<" error(s)\n";
        return false;
    }
    return true;
}
