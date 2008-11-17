//#define TEST

#include <iostream>
#include "global.h"

#ifdef TEST
#   include "test.h"
#endif

int main(int argc,const char ** argv){
    using namespace std;
#ifdef TEST
    //test_1();
    //test_2();
    test_3();
#else
    if(argc < 2){
        cerr<<"Usage: "<<argv[0]<<" file\n";
        return 1;
    }
    global().Init();
    if(!global().Compile(argv[1]))
        return 1;
    if(!global().Build())
        return 1;
#endif
    return 0;
}
