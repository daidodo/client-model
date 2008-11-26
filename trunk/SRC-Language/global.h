#ifndef DOZERG_GLOBAL_H_20081111
#define DOZERG_GLOBAL_H_20081111

#include "program.h"
#include "runtime.h"
#include "common/SharedPtr.h"

struct CGlobal
{
    static const int MAX_ERRORS = 0;
    //parse infos
    int lineno;
    int err_count_;
    std::string input_file;
    std::string cur_tok;
    //program
    CSharedPtr<CProgram> program_;
    //runtime
    CSharedPtr<CRuntime> runtime_;
private:
    CGlobal(){}
    ~CGlobal(){}
public:
    static CGlobal & Inst(){
        static CGlobal inst;
        return inst;
    }
    void ErrFound();
    void Init();
    bool Compile(const std::string & fname);
    bool Run();
};

inline CGlobal & global(){return CGlobal::Inst();}

inline CProgram & program(){return *global().program_;}

inline CRuntime & runtime(){return *global().runtime_;}

#define CUR_TOK     (global().cur_tok)
#define CUR_CMD     (program().CurCmd())
#define CUR_VTB     (program().CurVarTable())
#define LINE_NO     (global().lineno)
#define ERR_INCR    {global().ErrFound();}

#endif
