#include "SRC_language.h"
#include "global.h"

void SRC_init()
{
    global().Init();
}

bool SRC_compile(const std::string & filename)
{
    return global().Compile(filename);
}

bool SRC_run(int argc,const char * const * argv)
{
    return global().Run(argc,argv);
}

bool SRC_register_function(const std::string & func_name,
    bool (*func_ptr)(std::vector<char> & src,std::vector<char> & dst))
{
    return global().AddFunc(func_name,func_ptr);
}
