#ifndef DOZERG_GLOBAL_H_20081111
#define DOZERG_GLOBAL_H_20081111

#include <map>
#include <cassert>
#include "symbols.h"

struct CGlobal
{
    static const int MAX_ERRORS = 3;
    //parse infos
    int lineno;
    int err_count_;
    std::string input_file;
    std::string cur_tok;
    CProgram program_;
private:
    CGlobal():lineno(1),err_count_(0){}
public:
    static CGlobal & Inst(){
        static CGlobal inst;
        return inst;
    }
    void ErrIncrease(){
        if(++err_count_ > MAX_ERRORS)
            exit(1);
    }
};

inline CGlobal & global(){return CGlobal::Inst();}

inline CProgram & program(){return global().program_;}

#define CUR_TOK     (global().cur_tok)
#define CUR_CMD     (program().cur_cmd)
#define LINE_NO     (global().lineno)
#define ERR_INCR    {global().ErrIncrease();}

#endif
