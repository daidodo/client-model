#ifndef DOZERG_GLOBAL_H_20081111
#define DOZERG_GLOBAL_H_20081111

#include <map>
#include <cassert>
#include "symbols.h"

class CGlobal
{
    CGlobal()
        : lineno(1)
        , tcp_default(true)
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
            CVariable * ret = New<CVariable>(lineno);
            ret->varname_ = varname;
            var_table[varname] = ret;
            return ret;
        }else
            return wh->second;
    }
    const std::string & GetQstr(size_t i) const{
        assert(i < qstr_table.size());
        return qstr_table[i];
    }
//members:
    //parse infos
    std::string input_file;
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

#define CUR_TOK (global().cur_tok)
#define LINE_NO (global().lineno)

#endif
