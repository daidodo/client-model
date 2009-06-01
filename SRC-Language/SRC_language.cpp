#include "SRC_language.h"
#include "global.h"

void SRC_init()
{
    global().Init();
}

bool SRC_compile(const char * filename)
{
    return global().Compile(filename);
}

bool SRC_run(int argc,const char * const * argv)
{
    return global().Run(argc,argv);
}

bool SRC_register_function(const char * func_name,__SRC_UserFunc func_ptr,unsigned int dst_len_max)
{
    return global().AddFunc(func_name,func_ptr,dst_len_max);
}
