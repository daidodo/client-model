#ifndef DOZERG_GLOBAL_H_20081111
#define DOZERG_GLOBAL_H_20081111

#include "runtime.h"

struct CGlobal
{
    typedef std::vector<char>   __Buf;
    typedef bool (*__Func)(__Buf &,__Buf &);
    static const int MAX_ERRORS = 3;
    //parse infos
    int lineno;
    int err_count_;
    std::string input_file;
    std::string cur_tok;
    //program
    CSharedPtr<CProgram> program_;
    //runtime
    CSharedPtr<CRuntime> runtime_;
    //functions
    std::map<std::string,__Func> func_map_;
private:
    CGlobal(){}
    ~CGlobal(){}
    bool outputErrMsg() const;
public:
    static CGlobal & Inst(){
        static CGlobal inst;
        return inst;
    }
    void ErrFound();
    void Init();
    bool Compile(const std::string & fname);
    bool Run(int argc,const char * const * argv);
    bool AddFunc(const std::string func_name,__Func func_ptr);
    __Func FindFunc(const std::string func_name) const;
};

inline CGlobal & global(){return CGlobal::Inst();}

inline CProgram & program(){return *global().program_;}

inline CRuntime & runtime(){return *global().runtime_;}

#define CUR_TOK     (global().cur_tok)
#define CUR_CMD     (program().CurCmd())
#define CUR_VTB     (program().CurVarTable())
#define LINE_NO     (global().lineno)
#define ERR_INCR    {global().ErrFound();}
#define PM_ARG(i)   (runtime().ProgArg(i))

#endif
