#include <cassert>  //assert
#include <cstddef>  //size_t
#include <cstdlib>  //atoi,atol
#include "util.h"

template<typename T,int Bytes = sizeof(T)>
struct __NumUnit{};

template<typename T>struct __NumUnit<T,2>{
    T operator ()(T v,int u) const{
        switch(u){
            case 'k':case 'K':  //kilo
                v <<= 10;
                break;
            default:;
        }
        return v;
    }
};

template<typename T>struct __NumUnit<T,4>{
    T operator ()(T v,int u) const{
        switch(u){
            case 'k':case 'K':  //kilo
                v <<= 10;
                break;
            case 'm':case 'M':  //maga
                v <<= 20;
                break;
            case 'g':case 'G':  //giga
                v <<= 30;
                break;
            default:;
        }
        return v;
    }
};

template<typename T>struct __NumUnit<T,8>{
    T operator ()(T v,int u) const{
        switch(u){
            case 'k':case 'K':  //kilo
                v <<= 10;
                break;
            case 'm':case 'M':  //maga
                v <<= 20;
                break;
            case 'g':case 'G':  //giga
                v <<= 30;
                break;
            case 't':case 'T':  //tera
                v <<= 40;
                break;
            case 'p':case 'P':  //peta
                v <<= 50;
                break;
            case 'e':case 'E':  //egza
                v <<= 60;
                break;
            default:;
        }
        return v;
    }
};

template<typename T>
inline int __number_unit(T v,int u)
{
    return __NumUnit<T>()(v,u);
}

template<typename T>
T str2num_base16(const char * str,size_t len)
{
    assert(str && len);
    T ret = 0;
    for(size_t i = 0;i < len;++i){
        if(str[i] >= '0' && str[i] <= '9')
            ret = (ret << 4) + str[i] - '0';
        else if(str[i] >= 'a' && str[i] <= 'f')
            ret = (ret << 4) + str[i] - 'a' + 10;
        else if(str[i] >= 'A' && str[i] <= 'F')
            ret = (ret << 4) + str[i] - 'A' + 10;
        else
            break;
    }
    return ret;
}

template<typename T>
T str2num_base8(const char * str,size_t len)
{
    assert(str && len);
    if(*str == 'x' || *str == 'X')
        return str2num_base16<T>(str + 1,len - 1);
    T ret = 0;
    for(size_t i = 0;i < len;++i){
        if(str[i] >= '0' && str[i] <= '7')
            ret = (ret << 3) + str[i] - '0';
        else
            break;
    }
    return ret;
}

int str2int(const char * str,size_t len)
{
    assert(str && len);
    int ret = 0;
    if(*str == '+')
        return str2int(str + 1,len - 1);
    if(*str == '-')
        return -str2int(str + 1,len - 1);
    if(*str == '0'){
        if(len > 1)
            ret = str2num_base8<int>(str + 1,len - 1);
    }else
        ret = atoi(str);
    return __number_unit(ret,str[len - 1]);
}

long str2long(const char * str,size_t len)
{
    assert(str && len);
    if(*str == '+')
        return str2long(str + 1,len - 1);
    if(*str == '-')
        return -str2long(str + 1,len - 1);
    long ret = 0;
    if(*str == '0'){
        if(len > 1)
            ret = str2num_base8<long>(str + 1,len - 1);
    }else
        ret = atol(str);
    return __number_unit(ret,str[len - 1]);
}

long long str2i64(const char * str,size_t len)
{
    assert(str && len);
    if(*str == '+')
        return str2i64(str + 1,len - 1);
    if(*str == '-')
        return -str2i64(str + 1,len - 1);
    long long ret = 0;
    if(*str == '0'){
        if(len > 1)
            ret = str2num_base8<long>(str + 1,len - 1);
    }else
        ret = atoll(str);
    return __number_unit(ret,str[len - 1]);
}

