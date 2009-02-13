//#define TEST

#include <iostream>
#include "SRC_language.h"

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
        cerr<<"Usage: "<<argv[0]<<" FILE\n";
        return 1;
    }
    SRC_init();
    if(!SRC_compile(argv[1]))
        return 1;
    if(!SRC_run(argc,argv))
        return 1;
#endif
    return 0;
}
