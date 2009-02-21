#ifndef DOZERG_RUNTIME_H_20081115
#define DOZERG_RUNTIME_H_20081115

#include <string>
#include <list>
#include <vector>
#include <map>
#include "program.h"
#include "rt_structs.h"

struct CRuntime
{
    typedef std::list<std::string>              __VnameList;
    typedef __VnameList::iterator               __VnameIter;
    typedef std::map<std::string,__VnameIter>   __VnameMap;
    //program arguments
    int argc_;
    const char * const * argv_;
    //connections
    CSharedPtr<CValue> default_conn_;  //默认连接
    //variables
    std::map<std::string,CSharedPtr<CDeclare> > var_table_;
    __VnameList post_list_;     //延后求值列表
    __VnameMap  post_map_;
    //byte order
    bool net_byte_order_;      //当前的字节序设置
//functions:
    CRuntime();
    void SetProgArgs(int argc,const char * const * argv){argc_ = argc;argv_ = argv;}
    void Interpret(CProgram & program);
    void SetByteOrder(bool net_bo){net_byte_order_ = net_bo;}
    CSharedPtr<CDeclare> FindVar(std::string vname,CSharedPtr<CCmdStruct> cmd = 0);
    double Priority(const std::string & vname) const;
    bool IsPost(const std::string & vname) const;
    static std::string RealVarname(const std::string & name);
    const char * ProgArg(int i) const{return (argv_ && i >= 0 && i < argc_ ? argv_[i] : 0);}
private:
    bool addPostVar(const std::string & vname,CSharedPtr<CDeclare> decl,const std::string & depend);
    void addPostVar(const std::string & vname,CSharedPtr<CDeclare> decl);
    void addConnection(CSharedPtr<CValue> conn);
    static std::string localVarname(const std::string & name,const std::string & suffix);
    double maxPriority() const;
    void postEvaluate(CSharedPtr<CCmdStruct> cmd);
    //top
    void processStmt(CSharedPtr<CStmt> stmt,CSharedPtr<CCmdStruct> cmd);
    //level 1
    void processAssertExp(CSharedPtr<CAssertExp> ass,CSharedPtr<CCmdStruct> cmd,std::vector<int> & lines);
    void processDeclare(CSharedPtr<CDeclare> decl,CSharedPtr<CCmdStruct> cmd,std::vector<int> & lines);
    void processFunc(CSharedPtr<CFuncCall> func,CSharedPtr<CCmdStruct> cmd,std::vector<int> & lines);
    void processCmd(CSharedPtr<CCmdStruct> cmd,CSharedPtr<CCmdStruct> host_cmd,std::vector<int> & lines);
    //level 2
    void processArray(CSharedPtr<CDeclare> decl,CSharedPtr<CCmdStruct> cmd,std::vector<int> & lines);
    void processPost(CSharedPtr<CDeclare> decl,CSharedPtr<CCmdStruct> cmd,std::vector<int> & lines);
    void processFixed(CSharedPtr<CDeclare> decl,CSharedPtr<CCmdStruct> cmd,std::vector<int> & lines);
    void processDeclAssert(CSharedPtr<CDeclare> decl,CSharedPtr<CCmdStruct> cmd,std::vector<int> & lines);
    void processStreamIn(CSharedPtr<CDeclare> decl,CSharedPtr<CCmdStruct> cmd,std::vector<int> & lines);
    void processStreamOut(CSharedPtr<CDeclare> decl,CSharedPtr<CCmdStruct> cmd,std::vector<int> & lines);
};

#endif
