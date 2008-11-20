#ifndef DOZERG_UTILITY_H_20081111
#define DOZERG_UTILITY_H_20081111

#include <string>
#include <vector>
#include <byteswap.h>   //bswap_16,bswap_32,bswap_64

template<typename T>
T str2num_base16(const char * str,size_t len);

template<typename T>
T str2num_base8(const char * str,size_t len);

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

#endif
