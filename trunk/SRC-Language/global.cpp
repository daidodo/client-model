#include "global.h"

CGlobal::CGlobal()
    : lineno(1)
    , tcp_default(true)
    , cur_cmd(0)
{}

CGlobal::~CGlobal()
{
    //vars and stmts
    for(std::map<std::string,CVariable *>::iterator i = var_table.begin();i != var_table.end();++i)
        Delete(i->second);
    std::for_each(global_stmts.begin(),global_stmts.end(),Delete<CStmt>);
    //connections
    std::for_each(tcp_table.begin(),tcp_table.end(),Delete<CTcp>);
    std::for_each(udp_table.begin(),udp_table.end(),Delete<CUdp>);
    //commands
    for(std::map<std::string,CCommand *>::iterator i = cmd_table.begin();i != cmd_table.end();++i)
        Delete(i->second);
}

CVariable * CGlobal::GetVar(const std::string & varname){
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

void CGlobal::AddStmt(CAssertExp * stmt)
{
}

void CGlobal::AddStmt(CDeclare * stmt)
{
}

void CGlobal::AddStmt(CFuncCall * stmt)
{
}

void CGlobal::CmdBegin(CVariable * var_name)
{
}

void CGlobal::CmdEnd()
{
}

