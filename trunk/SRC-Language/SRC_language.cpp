#include "SRC_language.h"
#include "global.h"

SRCLIBRARY_API void SRC_init()
{
    global().Init();
}

SRCLIBRARY_API bool SRC_compile(const std::string & filename)
{
    return global().Compile(filename);
}

SRCLIBRARY_API bool SRC_run(int argc,const char * const * argv)
{
    return global().Run(argc,argv);
}

SRCLIBRARY_API bool SRC_register_function(const std::string & func_name,
    bool (*func_ptr)(std::vector<char> & src,std::vector<char> & dst))
{
    return global().AddFunc(func_name,func_ptr);
}
