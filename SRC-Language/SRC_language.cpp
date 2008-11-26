#include "global.h"

void SRC_init()
{
    global().Init();
}

bool SRC_compile(const char * filename)
{
    return global().Compile(filename);
}

bool SRC_run()
{
    return global().Run();
}
