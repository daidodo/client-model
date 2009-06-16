#ifndef DOZERG_GLOBAL_H_20081111
#define DOZERG_GLOBAL_H_20081111

#include "runtime.h"
#include "SRC_language.h"

struct CGlobal
{
    struct __FunNode{
        __SRC_UserFunc func_;
        unsigned int dst_len_max_;
        __FunNode():func_(0),dst_len_max_(0){}
    };
    typedef std::map<std::string,__FunNode> __FuncMap;
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
    __FuncMap func_map_;
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
    bool Compile(const char * fname);
    bool Run(int argc,const char * const * argv);
    bool AddFunc(const char * func_name,__SRC_UserFunc func_ptr,unsigned int dst_len_max);
    const __FunNode * FindFunc(const std::string func_name) const{
        __FuncMap::const_iterator wh = func_map_.find(func_name);
        return (wh == func_map_.end() ? 0 : &wh->second);
    }
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
