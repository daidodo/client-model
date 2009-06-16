#include <fstream>
#include "util.h"

using namespace std;

//c-string
void test_1()
{
    const char * RESULT =
"t\0533\
h\"\\is\
"
    ;
    cout<<RESULT<<endl;
}

//c-char
void test_2()
{
    const char a = '\
a\
';
    cout<<a<<endl;
}

//string to number
void test_3()
{
    string str = "-0x123uLK";
    cout<<str2int(str.c_str(),str.length())<<endl;
}

//performance test
void test_4(int argc,const char ** argv)
{
    if(argc < 2){
        cerr<<"Usage: "<<argv[0]<<" FILE\n";
        return;
    }
    SRC_init();
    if(!SRC_compile(argv[1])){
        cerr<<"compile error\n";
        return;
    }
    if(!SRC_run(argc,argv))
        cerr<<"run error\n";
}
