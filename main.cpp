//#define TEST

#include <iostream>
#include "SRC_language.h"

#ifdef TEST
#   include "test.h"
#endif

bool aes_encrypt(std::vector<char> & src,std::vector<char> & dst)
{
    dst.swap(src);
    return true;
}

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
    SRC_init();
    if(!SRC_register_function("aes_encrypt",aes_encrypt))
        return 1;
    if(!SRC_register_function("aes_decrypt",aes_encrypt))
        return 1;
    if(!SRC_compile(argv[1]))
        return 1;
    if(!SRC_run())
        return 1;
#endif
    return 0;
}
