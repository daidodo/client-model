#ifndef DOZERG_GLOBAL_H_20081111
#define DOZERG_GLOBAL_H_20081111

#include <map>
#include "symbols.h"

class CGlobal
{
    CGlobal()
        : input_file(0)
        , lineno(1)
        , cur_cmd(0)
    {}
    ~CGlobal(){
        //string vars
        for(std::map<std::string,CVariable *>::iterator i = var_table.begin();i != var_table.end();++i)
            Delete(i->second);
        //connections
        std::for_each(tcp_table.begin(),tcp_table.end(),Delete<CTcp>);
        std::for_each(udp_table.begin(),udp_table.end(),Delete<CUdp>);
        //commands
        for(std::map<std::string,CCommand *>::iterator i = cmd_table.begin();i != cmd_table.end();++i)
            Delete(i->second);
    }
public:
    static CGlobal & Inst(){
        static CGlobal inst;
        return inst;
    }
    CVariable * GetVar(const std::string & varname){
        typedef std::map<std::string,CVariable *>::const_iterator __Iter;
        __Iter wh = var_table.find(varname);
        if(wh == var_table.end()){
            CVariable * ret = New<CVariable>();
            ret->varname_ = varname;
            ret->type_ = 0;
            return (var_table[varname] = ret);
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
    std::map<std::string,CVariable *> var_table;
    //connections
    bool tcp_default;
    std::vector<CTcp *> tcp_table;
    std::vector<CUdp *> udp_table;
    //commands
    CCommand * cur_cmd;
    std::map<std::string,CCommand *> cmd_table;
    //global stmts
    std::vector<CStmt *> global_stmts;
};

inline CGlobal & global(){return CGlobal::Inst();}

#endif
