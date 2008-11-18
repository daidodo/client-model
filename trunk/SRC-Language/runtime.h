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
    typedef __VnameList::iterator               __VnameIter;
    typedef std::map<std::string,__VnameIter>   __VnameMap;
    //connections
    CSharedPtr<CTcp> default_tcp_;
    CSharedPtr<CUdp> default_udp_;
    //variables
    std::map<std::string,CSharedPtr<CDeclare> > var_table_;
    __VnameList post_list_;     //延后求值列表
    __VnameMap  post_map_;
    //stmt list
    __StmtList stmts_list_;
//functions:
    void Interpret(CProgram & program);
    CSharedPtr<CDeclare> FindVar(std::string vname);
    double Priority(const std::string & vname) const;
    bool IsPost(const std::string & vname) const;
private:
    bool addPostVar(const std::string & vname,CSharedPtr<CDeclare> decl,const std::string & depend);
    void addPostVar(const std::string & vname,CSharedPtr<CDeclare> decl);
    void addConnection(CSharedPtr<CValue> conn);
    //level 1
    void processDeclare(CSharedPtr<CDeclare> decl);
    void processFunc(CSharedPtr<CFuncCall> func);
    void processCmd(CSharedPtr<CCmd> cmd);
    //level 2
    void processPost(CSharedPtr<CDeclare> decl);
    void processFixed(CSharedPtr<CDeclare> decl);
};

#endif
