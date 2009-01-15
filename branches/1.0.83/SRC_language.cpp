#include "SRC_language.h"
#include "global.h"

EXPORT_API void SRC_init()
{
    global().Init();
}

EXPORT_API bool SRC_compile(const std::string & filename)
{
    return global().Compile(filename);
}

EXPORT_API bool SRC_run()
{
    return global().Run();
}

EXPORT_API bool SRC_register_function(const std::string & func_name,
    bool (*func_ptr)(std::vector<char> & src,std::vector<char> & dst))
{
    return global().AddFunc(func_name,func_ptr);
}
