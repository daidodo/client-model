#include <fstream>
#include "util.h"

using namespace std;

//qstr()
void test_1()
{
    const char * TEST_FILE = "test.txt";
    ifstream inf(TEST_FILE);
    if(!inf.is_open()){
        cerr<<"cannot open "<<TEST_FILE<<endl;
        return;
    }
    string src;
    std::getline(inf,src,char(0));
    string res;
    int n = qstr(res,src.c_str(),src.length());
    cout<<"n = "<<n<<endl;
    cout<<res.c_str()<<endl;
    const char * RESULT =
"t\0533\
h\"\\is\
"
    ;
    cout<<RESULT<<endl;
}
