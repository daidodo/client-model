#include <cassert>  //assert
#include <cstddef>  //size_t
#include <cstdlib>  //atoi,atol
#include <sstream>  //std::ostringstream
#include <iomanip>  //std::setw
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
    return int(__NumUnit<T>()(v,u));
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
    }else{
        ret = 0;
        std::istringstream iss(str);
        iss>>ret;
    }
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

std::string DumpStr(const char * v,size_t sz,char replace,bool hasLen)
{
    const char DEFAULT = '.';
    const char TRAN_CHAR = '\\';
    const char FOLLOW_CHAR[] = "abtnvfr";
    assert(v);
    if(!IsReadable(replace))
        replace = DEFAULT;
    std::string ret;
    if(hasLen){
        std::ostringstream oss;
        oss<<"("<<sz<<")";
        ret = oss.str();
    }
    ret.reserve(ret.size() + sz + (sz >> 2));
    for(;sz > 0;--sz,++v){
        if(*v == TRAN_CHAR){
            ret.push_back(TRAN_CHAR);
            ret.push_back(TRAN_CHAR);
        }else if(*v >= '\a' && *v <= '\r'){
            ret.push_back(TRAN_CHAR);
            ret.push_back(FOLLOW_CHAR[*v - '\a']);
        }else if(!*v){
            ret.push_back(TRAN_CHAR);
            ret.push_back('0');
        }else
            ret.push_back(IsReadable(*v) ? *v : replace);
    }
    return ret;
}

std::string DumpVal(const char * v,size_t sz,int base,bool hasLen)
{
    const char TRAN_CHAR = '\\';
    const char FOLLOW_CHAR[] = "abtnvfr";
    const char DIGIT[] = "0123456789ABCDEF";
    assert(v);
    std::string ret;
    if(hasLen){
        std::ostringstream oss;
        oss<<"("<<sz<<")";
        ret = oss.str();
    }
    ret.reserve(ret.length() + 2 * sz);
    for(;sz > 0;--sz,++v){
        if(*v == TRAN_CHAR){
            ret.push_back(TRAN_CHAR);
            ret.push_back(TRAN_CHAR);
        }else if(IsReadable(*v))
            ret.push_back(*v);
        else{
            ret.push_back(TRAN_CHAR);
            if(*v >= '\a' && *v <= '\r')
                ret.push_back(FOLLOW_CHAR[*v - '\a']);
            else if(!*v)
                ret.push_back('0');
            else{
                switch(base){
                    case 16:{       //16进制
                        ret.push_back(DIGIT[(*v >> 4) & 0xF]);
                        ret.push_back(DIGIT[*v & 0xF]);
                        break;}
                    default:       //8进制
                        ret.push_back(DIGIT[(*v >> 6) & 3]);
                        ret.push_back(DIGIT[(*v >> 3) & 7]);
                        ret.push_back(DIGIT[*v & 7]);
                }
            }
        }
    }
    return ret;
}

//预读取前PRE_READ个字符，统计可读字符个数，然后选择合适的转换函数
std::string Dump(const char * v,size_t sz,size_t show_sz,bool hasLen)
{
    const size_t PRE_READ = 32;
    std::string ret;
    if(hasLen){
        std::ostringstream oss;
        oss<<"("<<sz<<")";
        ret = oss.str();
    }
    size_t readable = 0;
    size_t check_len = std::min(sz,PRE_READ);
    for(const char *t = v,*e = v + check_len;t < e;++t)
        if(*t && IsReadable(*t))
            ++readable;
    if(readable <= (check_len >> 1))
        ret += DumpHex(v,std::min(sz,show_sz),' ',false);
    else if(readable < check_len)
        ret += DumpVal(v,std::min(sz,show_sz),8,false);
    else
        ret += DumpStr(v,std::min(sz,show_sz),'.',false);
    if(show_sz < sz)
        ret += "...";
    return ret;
}

std::string UnHex(const char * v,size_t sz)
{
    if(!v || !sz)
        return "";
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

std::string DumpFormat(const char * v,size_t sz)
{
    if(!v || !sz)
        return "";
    const size_t LINE_WIDTH = 4;
    const size_t CHARS_PER_LINE = 16;
    std::ostringstream oss;
    oss.fill('0');
    oss<<std::hex;
    for(size_t ln = 0;ln < sz;ln += CHARS_PER_LINE){
        oss<<std::setw(LINE_WIDTH)<<ln<<"h: ";
        const size_t left = std::min(CHARS_PER_LINE,sz - ln);
        oss<<DumpHex(v + ln,left,' ',false);
        for(size_t i = left;i < CHARS_PER_LINE;++i)
            oss<<"   ";
        oss<<"; ";
        for(size_t i = 0;i < left;++i)
            oss<<((v[ln + i] > 31 && v[ln + i] < 127) ? v[ln + i] : '.');
        oss<<std::endl;
    }
    return oss.str();
}

