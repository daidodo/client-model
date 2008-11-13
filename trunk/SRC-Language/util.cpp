#include <cassert>  //assert
#include <cstddef>  //size_t
#include <cstdlib>  //atoi
#include "util.h"

int str2int(const char * str,size_t len)
{
    assert(str && len);
    int ret = atoi(str);
    switch(str[len - 1]){
        case 'k':case 'K':
            ret <<= 10;
            break;
        case 'm':case 'M':
            ret <<= 20;
            break;
        case 'g':case 'G':
            ret <<= 30;
            break;
        default:;
    }
    return ret;
}

int atoi_base8(const char * str,size_t len)
{
    assert(str && len);
    int ret = 0;
    for(size_t i = 0;i < len;++i){
        assert(str[i] >= '0' && str[i] <= '7');
        ret = (ret << 3) + str[i] - '0';
    }
    return ret;
}

int atoi_base16(const char * str,size_t len)
{
    assert(str && len);
    int ret = 0;
    for(size_t i = 0;i < len;++i){
        ret <<= 4;
        if(str[i] >= '0' && str[i] <= '9')
            ret += str[i] - '0';
        else if(str[i] >= 'a' && str[i] <= 'f')
            ret += str[i] - 'a' + 10;
        else if(str[i] >= 'A' && str[i] <= 'F')
            ret += str[i] - 'A' + 10;
        else
            assert(0);
    }
    return ret;
}
