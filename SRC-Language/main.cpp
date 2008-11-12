//#define TEST

#include "common.h"
#include "global.h"

#ifdef TEST
#   include "test.h"
#endif

int main(int argc,const char ** argv){
    using namespace std;
#ifdef TEST
    test_1();
#else
    if(argc < 2){
        cerr<<"Usage: "<<argv[0]<<" file\n";
        exit(1);
    }
    FILE * fp = fopen(argv[1],"r");
    if(!fp){
        cerr<<"cannot open file '"<<argv[1]<<"'\n";
        exit(1);
    }
    global().input_file = argv[1];
    yyin = fp;
    if(yyparse()){
        cerr<<"parse failed\n";
        return 1;
    }
#endif
    return 0;
}
