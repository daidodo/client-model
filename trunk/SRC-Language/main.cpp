//#define TEST

#include <iostream>
#include "global.h"

extern FILE * yyin;

int yyparse();

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
    FILE * fp = fopen(argv[1],"r");
    if(!fp){
        cerr<<"cannot open file '"<<argv[1]<<"'\n";
        return 1;
    }
    global().input_file = argv[1];
    yyin = fp;
    yyparse();
    err_exit(0);
#endif
    return 0;
}
