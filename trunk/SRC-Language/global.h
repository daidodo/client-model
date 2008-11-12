#ifndef DOZERG_GLOBAL_H_20081111
#define DOZERG_GLOBAL_H_20081111

#include <string>
#include <vector>
#include <map>
#include "common.h"
#include "mm.h"

class CGlobal
{
    CGlobal()
        : input_file(0)
        , lineno(1)
        , cur_cmd(0)
    {}
    ~CGlobal(){
        typedef std::map<std::string,CArg *>::iterator __Iter;
        for(__Iter i = arg_table.begin();i != arg_table.end();++i)
            Delete(i->second);
    }
public:
    static CGlobal & Inst(){
        static CGlobal inst;
        return inst;
    }
    CArg * GetArg(const std::string & argname){
        typedef std::map<std::string,CArg *>::const_iterator __Iter;
        __Iter wh = arg_table.find(argname);
        if(wh == arg_table.end()){
            CArg * ret = New<CArg>();
            ret->argname_ = argname;
            ret->type_ = 0;
            return (arg_table[argname] = ret);
        }else
            return wh->second;
    }
//members:
    //parse infos
    const char * input_file;
    int lineno;
    std::string cur_tok;
    //string vars
    std::vector<std::string> qstr_table;
    std::map<std::string,CArg *> arg_table;
    //connections
    bool tcp_default;
    std::vector<CTcp *> tcp_table;
    std::vector<CUdp *> udp_table;
    //commands
    CCommand * cur_cmd;
    std::map<std::string,CCommand *> cmd_table;
};

inline CGlobal & global(){return CGlobal::Inst();}

#endif
