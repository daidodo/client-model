#define _CRT_SECURE_NO_WARNINGS 1

#include <cassert>
#include <iostream>
#include "global.h"
#include "errors.h"

extern FILE * yyin;

int yyparse();

bool CGlobal::outputErrMsg() const
{
    if(err_count_){
        std::cerr<<"total "<<err_count_<<" error";
        if(err_count_ > 1)
            std::cerr<<"s";
        std::cerr<<std::endl;
        return false;
    }
    return true;
}

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
    return outputErrMsg();
}

bool CGlobal::Run(int argc,const char * const * argv)
{
    if(!program_){
        std::cerr<<"program not ready!\n";
        return false;
    }
    if(err_count_){
        std::cerr<<"please fix errors first!\n";
        return false;
    }
    runtime_ = New<CRuntime>();
    runtime_->SetProgArgs(argc,argv);
    try{
        if(!InitSocket()){
            std::cerr<<"could not find a usable WinSock DLL\n";
            return false;
        }
        runtime_->Interpret(*program_);
        UninitSocket();
    }catch(int){}
    return outputErrMsg();
}

bool CGlobal::AddFunc(const std::string func_name,__Func func_ptr)
{
    assert(func_ptr);
    __Func & fp = func_map_[func_name];
    if(fp)
        return false;
    fp = func_ptr;
    return true;
}

CGlobal::__Func CGlobal::FindFunc(const std::string func_name) const
{
    std::map<std::string,__Func>::const_iterator wh = func_map_.find(func_name);
    return (wh == func_map_.end() ? 0 : wh->second);
}
