#include "SRC_language.h"
#include "global.h"

SRCDLL_API void SRC_init()
{
    global().Init();
}

SRCDLL_API bool SRC_compile(const char * filename)
{
    return global().Compile(filename);
}

SRCDLL_API bool SRC_run(int argc,const char * const * argv)
{
    return global().Run(argc,argv);
}

SRCDLL_API bool SRC_register_function(const char * func_name,__SRC_UserFunc func_ptr,unsigned int dst_len_max)
{
    return global().AddFunc(func_name,func_ptr,dst_len_max);
}
