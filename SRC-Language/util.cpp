#include <cassert>  //assert
#include <cstddef>  //size_t
#include <cstdlib>  //atoi,atol
#include <sstream>  //std::ostringstream
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

std::string DumpHex(const char * v,size_t sz,char sep,bool hasLen)
{
    const char DIGIT[] = "0123456789ABCDEF";
    assert(v);
    std::string ret;
    if(hasLen){
        std::ostringstream oss;
        oss<<"("<<sz<<")";
        ret = oss.str();
    }
    ret.reserve(ret.size() + (2 + (sep ? 1 : 0)) * sz);
    for(size_t i = 0;i < sz;++i){
        ret.push_back(DIGIT[(v[i] >> 4) & 0xF]);
        ret.push_back(DIGIT[v[i] & 0xF]);
        if(sep)
            ret.push_back(sep);
    }
    return ret;
}

std::string UnHex(const char * v,size_t sz)
{
    assert(v && sz);
    std::string ret;
    ret.reserve(sz >> 1);
    for(size_t i = 1;i < sz;i += 2){
        int t1 = UnHexChar(v[i - 1]);
        int t2 = UnHexChar(v[i]);
        if(t1 < 0 || t2 < 0)
            break;
        ret.push_back((t1 << 4) + t2);
    }
    return ret;
}

