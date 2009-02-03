#ifndef DOZERG_UTILITY_H_20081111
#define DOZERG_UTILITY_H_20081111

#include "platform.h"   //undef max,min
#include <string>
#include <vector>

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

int str2int(const char * str,size_t len);

long str2long(const char * str,size_t len);

long long str2i64(const char * str,size_t len);

template<class Ptr>
std::string to_str(Ptr p){
    return (p ? p->ToString() : "0x0");
}

template<class Ptr>
std::string signa(Ptr p){
    return (p ? p->Signature() : "0x0");
}

//字符a是否是可读，即ASCII码属于[32,126]
inline bool IsReadable(unsigned char a){
    return a > 31 && !(a & 0x80);
}

inline bool IsReadable(signed char a){
    return IsReadable((unsigned char)a);
}

inline bool IsReadable(char a){
    return IsReadable((unsigned char)a);
}

//得到数据v的16进制字符串表示
//默认格式示例："abc" = (3)61 62 63
//sep为分隔符,默认' '
//hasLen表示是否有前面的数据长度"(3)"
std::string DumpHex(const char * v,size_t sz,char sep = ' ',bool hasLen = true);

inline std::string DumpHex(const signed char * v,size_t sz,char sep = ' ',bool hasLen = true){
    return DumpHex((const char *)v,sz,sep,hasLen);
}

inline std::string DumpHex(const unsigned char * v,size_t sz,char sep = ' ',bool hasLen = true){
    return DumpHex((const char *)v,sz,sep,hasLen);
}

inline std::string DumpHex(const std::vector<char> & v,char sep = ' ',bool hasLen = true){
    return v.empty() ? (hasLen ? "(0)" : "") : DumpHex(&v[0],v.size(),sep,hasLen);
}

inline std::string DumpHex(std::string v,char sep = ' ',bool hasLen = true){
    return DumpHex(v.c_str(),v.length(),sep,hasLen);
}

//得到数据v的可打印形式，非可读字符用replace代替
//默认格式示例："a\t\0bc" = (5)a..bc
//replace为替代符,默认'.'
//hasLen表示是否有前面的数据长度"(5)"
std::string DumpStr(const char * v,size_t sz,char replace = '.',bool hasLen = true);

inline std::string DumpStr(const unsigned char * v,size_t sz,char replace = '.',bool hasLen = true){
    return DumpStr((const char *)v,sz,replace,hasLen);
}

inline std::string DumpStr(const signed char * v,size_t sz,char replace = '.',bool hasLen = true){
    return DumpStr((const char *)v,sz,replace,hasLen);
}

inline std::string DumpStr(const std::vector<char> & v,char replace = '.',bool hasLen = true){
    return v.empty() ? (hasLen ? "(0)" : "") : DumpStr(&v[0],v.size(),replace,hasLen);
}

inline std::string DumpStr(std::string str,char replace = '.',bool hasLen = true){
    return DumpStr(str.c_str(),str.length(),replace,hasLen);
}

//得到数据v的可打印形式，不可打印字符用base进制数值表示
//默认格式示例："a\t\223bc" = (5)a\t\223bc
//base取值为8，16
//hasLen表示是否有前面的数据长度"(5)"
std::string DumpVal(const char * v,size_t sz,int base = 8,bool hasLen = true);

inline std::string DumpVal(const unsigned char * v,size_t sz,char base = 8,bool hasLen = true){
    return DumpVal((const char *)v,sz,base,hasLen);
}

inline std::string DumpVal(const signed char * v,size_t sz,char base = 8,bool hasLen = true){
    return DumpVal((const char *)v,sz,base,hasLen);
}

inline std::string DumpVal(const std::vector<char> & v,char base = 8,bool hasLen = true){
    return v.empty() ? (hasLen ? "(0)" : "") : DumpVal(&v[0],v.size(),base,hasLen);
}

inline std::string DumpVal(std::string str,char base = 8,bool hasLen = true){
    return DumpVal(str.c_str(),str.length(),base,hasLen);
}

//得到数据v的可打印形式，自动选择DumpHex，DumpStr或DumpVal
//show_sz表示显示出来的数据长度，剩余的数据用"..."代替
//hasLen表示是否有前面的数据长度
std::string Dump(const char * v,size_t sz,size_t show_sz = size_t(-1),bool hasLen = true);

inline std::string Dump(const unsigned char * v,size_t sz,size_t show_sz = size_t(-1),bool hasLen = true){
    return Dump((const char *)v,sz,show_sz,hasLen);
}

inline std::string Dump(const signed char * v,size_t sz,size_t show_sz = size_t(-1),bool hasLen = true){
    return Dump((const char *)v,sz,show_sz,hasLen);
}

inline std::string Dump(const std::vector<char> & v,size_t show_sz = size_t(-1),bool hasLen = true){
    return v.empty() ? (hasLen ? "(0)" : "") : Dump(&v[0],v.size(),show_sz,hasLen);
}

inline std::string Dump(std::string str,size_t show_sz = size_t(-1),bool hasLen = true){
    return Dump(str.c_str(),str.length(),show_sz,hasLen);
}


//把数据的16进制还原成数据本身
std::string UnHex(const char * v,size_t sz);

inline std::string UnHex(const unsigned char * v,size_t sz){
    return UnHex((const char *)v,sz);
}

inline std::string UnHex(const signed char * v,size_t sz){
    return UnHex((const char *)v,sz);
}

inline std::string UnHex(const std::vector<char> & v){
    return UnHex(&v[0],v.size());
}

inline std::string UnHex(std::string v){
    return UnHex(v.c_str(),v.length());
}

//得到16进制字符a表示的10进制数值，错误时返回-1
inline int UnHexChar(char a){
    if(a >= '0' && a <= '9')
        return a - '0';
    else if(a >= 'a' && a <= 'f')
        return a - 'a' + 0xa;
    else if(a >= 'A' && a <= 'F')
        return a - 'A' + 0xA;
    else
        return -1;
}

inline int UnHexChar(signed char a){
    return UnHexChar(char(a));
}

inline int UnHexChar(unsigned char a){
    return UnHexChar(char(a));
}

//struct CByteOrderTraits
template<typename T,size_t N>
struct CByteOrderTraits{};

template<typename T>struct CByteOrderTraits<T,1>{
    static T Swap(T a){
        return a;
    }
};

template<typename T>struct CByteOrderTraits<T,2>{
    static T Swap(T a){
        return bswap_16(a);
    }
};

template<typename T>struct CByteOrderTraits<T,4>{
    static T Swap(T a){
        return bswap_32(a);
    }
};

template<typename T>struct CByteOrderTraits<T,8>{
    static T Swap(T a){
        return bswap_64(a);
    }
};

//改变v的byte order.要求T是原始数据类型
template<typename T>
T SwapByteOrder(T v){
    return CByteOrderTraits<T,sizeof(T)>::Swap(v);
}

//转换字符串为16进制，并显示可视的字符
std::string DumpFormat(const char * v,size_t sz);

inline std::string DumpFormat(const unsigned char * v,size_t sz){
    return DumpFormat((const char *)v,sz);
}

inline std::string DumpFormat(const signed char * v,size_t sz){
    return DumpFormat((const char *)v,sz);
}

inline std::string DumpFormat(const std::vector<char> & v){
    return DumpFormat(&v[0],v.size());
}

inline std::string DumpFormat(std::string v){
    return DumpFormat(v.c_str(),v.length());
}

#endif
