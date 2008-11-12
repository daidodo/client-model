#ifndef DOZERG_GLOBAL_H_20081111
#define DOZERG_GLOBAL_H_20081111

#include <string>
#include <vector>
#include <map>
#include "common.h"

class CGlobal
{
    CGlobal()
        : input_file(0)
        , lineno(1)
    {}
    ~CGlobal(){}
public:
    static CGlobal & Inst(){
        static CGlobal inst;
        return inst;
    }
    //members:
    std::vector<std::string> qstr_table;
    std::map<std::string,CExpr *> arg_table;
    std::string cur_tok;
    const char * input_file;
    int lineno;
};

inline CGlobal & global(){return CGlobal::Inst();}

#endif
