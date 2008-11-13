#ifndef DOZERG_GLOBAL_H_20081111
#define DOZERG_GLOBAL_H_20081111

#include <map>
#include <cassert>
#include "symbols.h"

struct CGlobal
{
    //parse infos
    std::string input_file;
    int lineno;
    std::string cur_tok;
    //vars and stmts
    std::vector<std::string> qstr_table;
    std::map<std::string,CVariable *> var_table;
    std::vector<CStmt *> global_stmts;
    //connections
    bool tcp_default;
    std::vector<CTcp *> tcp_table;
    std::vector<CUdp *> udp_table;
    //commands
    CCommand * cur_cmd;
    std::map<std::string,CCommand *> cmd_table;
private:
    CGlobal();
    ~CGlobal();
public:
    static CGlobal & Inst(){
        static CGlobal inst;
        return inst;
    }
    CVariable * GetVar(const std::string & varname);
    const std::string & GetQstr(size_t i) const{
        assert(i < qstr_table.size());
        return qstr_table[i];
    }
    void AddStmt(CAssertExp * stmt);
    void AddStmt(CDeclare * stmt);
    void AddStmt(CFuncCall * stmt);
    void CmdBegin(CVariable * var_name);
    void CmdEnd();
};

inline CGlobal & global(){return CGlobal::Inst();}

#define CUR_TOK (global().cur_tok)
#define LINE_NO (global().lineno)

#endif
