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
    CSharedPtr<CValue> default_conn_;  //Ĭ������
    //variables
    std::map<std::string,CSharedPtr<CDeclare> > var_table_;
    __VnameList post_list_;     //�Ӻ���ֵ�б�
    __VnameMap  post_map_;
    //byte order
    bool net_byte_order_;      //��ǰ���ֽ�������
//functions:
    CRuntime();
    void SetProgArgs(int argc,const char * const * argv){argc_ = argc - 1;argv_ = argv + 1;}
    void Interpret(CProgram & program);
    void SetByteOrder(bool net_bo){net_byte_order_ = net_bo;}
    CSharedPtr<CDeclare> FindVar(std::string vname,CSharedPtr<CCmd> cmd = 0);
    double Priority(const std::string & vname) const;
    bool IsPost(const std::string & vname) const;
    static std::string RealVarname(const std::string & name);
    const char * ProgArg(int i) const{return (argv_ && i >= 0 && i < argc_ ? argv_[i] : 0);}
private:
    bool addPostVar(const std::string & vname,CSharedPtr<CDeclare> decl,const std::string & depend);
    void addPostVar(const std::string & vname,CSharedPtr<CDeclare> decl);
    void addConnection(CSharedPtr<CValue> conn);
    static std::string localVarname(const std::string & name,const CCmd & cmd);
    double maxPriority() const;
    void postEvaluate(CSharedPtr<CCmd> cmd);
    //top
    void processStmt(CSharedPtr<CStmt> stmt,CSharedPtr<CCmd> cmd);
    //level 1
    void processAssertExp(CSharedPtr<CAssertExp> ass,CSharedPtr<CCmd> cmd);
    void processDeclare(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd);
    void processFunc(CSharedPtr<CFuncCall> func,CSharedPtr<CCmd> cmd);
    void processCmd(CSharedPtr<CCmd> cmd);
    //level 2
    void processArray(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd);
    void processPost(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd);
    void processFixed(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd);
    void processDeclAssert(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd);
    void processStreamIn(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd);
    void processStreamOut(CSharedPtr<CDeclare> decl,CSharedPtr<CCmd> cmd);
};

#endif