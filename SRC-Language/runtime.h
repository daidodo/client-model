#ifndef DOZERG_RUNTIME_H_20081115
#define DOZERG_RUNTIME_H_20081115

#include "program.h"

struct CRuntime
{
    typedef std::list<std::string>              __VnameList;
    typedef __VnameList::iterator               __VnameIter;
    typedef std::map<std::string,__VnameIter>   __VnameMap;
    //program arguments
    int argc_;
    const char * const * argv_;
    //connections
    CSharedPtr<CValue> default_conn_;   //默认连接
    //variables
    std::map<std::string,CSharedPtr<CDeclare> > var_table_;
    __VnameList post_list_;             //延后求值列表
    __VnameMap  post_map_;
    //byte order
    bool cur_byte_order_;               //当前的字节序设置
    //debug
    bool debug_;                        //是否输出调试信息
//functions:
    CRuntime();
    void SetProgArgs(int argc,const char * const * argv){argc_ = argc - 1;argv_ = argv + 1;}
    void Interpret(CProgram & program);
    void SetByteOrder(bool net_bo){cur_byte_order_ = net_bo;}
    CSharedPtr<CDeclare> FindVar(std::string vname,CSharedPtr<CCmd> cmd = 0);
    double Priority(const std::string & vname) const;
    bool IsPost(const std::string & vname) const;
    static std::string RealVarname(const std::string & name);
    const char * ProgArg(int i) const{return (argv_ && i >= 0 && i < argc_ ? argv_[i] : 0);}
    void Debug(bool dbg){debug_ = dbg;}
    bool Debug() const{return debug_;}
private:
    void addPostVar(const std::string & vname,CSharedPtr<CDeclare> decl,const std::string & depend);
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
