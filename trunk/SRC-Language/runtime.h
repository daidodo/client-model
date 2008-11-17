#ifndef DOZERG_RUNTIME_H_20081115
#define DOZERG_RUNTIME_H_20081115

#include <string>
#include <list>
#include <vector>
#include <map>
#include "program.h"

struct CRuntime
{
    typedef std::vector<CSharedPtr<CStmt> >     __StmtList;
    typedef std::list<std::string>              __VnameList;
    //typedef __VnameList::iterator               __VnameIter;
    //typedef std::map<std::string,__VnameIter>   __VnameMap;
    //connections
    bool default_tcp_;
    std::vector<CSharedPtr<CTcp> > tcp_table_;
    std::vector<CSharedPtr<CUdp> > udp_table_;
    //variables
    std::map<std::string,CSharedPtr<CDeclare> > var_table_;
    std::list<std::string> post_list_;     //延后求值列表
    //stmt list
    __StmtList stmts_list_;
//functions:
    CRuntime();
    bool Interpret(CProgram & program);
    CSharedPtr<CDeclare> FindVar(const std::string & vname);
private:
    //top
    void processStmt(CStmt & stmt);
    //level 1
    void processDeclare(CDeclare & decl);
    void processFunc(CFuncCall & func);
    void processCmd(CCmd & cmd);
    //level 2
    void processPost(CDeclare & decl);
    void processFixed(CDeclare & decl);
};

#endif
