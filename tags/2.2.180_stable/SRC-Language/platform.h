#ifndef DOZERG_PLATFORM_H_20090105
#define DOZERG_PLATFORM_H_20090105

#include <string>

#ifdef WIN32

#   include <Winsock2.h>
#   include <Ws2tcpip.h>    //inet_ntop,getaddrinfo,freeaddrinfo,gai_strerror
#   include <io.h>          //isatty
#   include <errno.h>       //EAGAIN
#   pragma comment(lib,"Ws2_32")

//This is very ugly!
//see <WinDef.h>
#   ifdef max
#       undef max
#   endif
#   ifdef min
#       undef min
#   endif

#   define MSG_NOSIGNAL 0
#   define EWOULDBLOCK  WSAEWOULDBLOCK

typedef __int8              S8;
typedef unsigned __int8     U8;
typedef __int16             S16;
typedef unsigned __int16    U16;
typedef __int32             S32;
typedef unsigned __int32    U32;
typedef __int64             S64;
typedef unsigned __int64    U64;

typedef S32 ssize_t;

template<typename T>
T bswap_16(T a){
    return (((a << 8) & 0xFF00) | ((a >> 8) & 0xFF));
}

template<typename T>
T bswap_32(T a){
    return (((a << 24) & 0xFF000000) |
        ((a << 8) & 0xFF0000) |
        ((a >> 8) & 0xFF00) |
        ((a >> 24) & 0xFF));
}

template<typename T>
T bswap_64(T a){
    return (((a << 56) & 0xFF00000000000000LL) |
        ((a << 40) & 0xFF000000000000LL) |
        ((a << 24) & 0xFF0000000000LL) |
        ((a << 8) & 0xFF00000000LL) |
        ((a >> 8) & 0xFF000000LL) |
        ((a >> 24) & 0xFF0000LL) |
        ((a >> 40) & 0xFF00LL) |
        ((a >> 56) & 0xFFLL));
}

bool InitSocket();

inline void UninitSocket(){WSACleanup();}

void sleep(unsigned int sec);

#else

#   include <sys/socket.h>
#   include <netinet/in.h>  //ntohl
#   include <byteswap.h>    //bswap_16,bswap_32,bswap_64
#   include <arpa/inet.h>   //inet_ntop,sockaddr_in
#   include <sys/poll.h>    //poll
#   include <netdb.h>       //getaddrinfo,freeaddrinfo,gai_strerror
#   include <errno.h>       //errno
#   include <cstring>       //strerror_r

#if defined(__GNUC__)
#   include <stdint.h>
//basic types
typedef int8_t              S8;
typedef uint8_t             U8;
typedef int16_t             S16;
typedef uint16_t            U16;
typedef int32_t             S32;
typedef uint32_t            U32;
typedef int64_t             S64;
typedef uint64_t            U64;
#else   //platform dependenty
typedef signed char         S8;
typedef unsigned char       U8;
typedef short               S16;
typedef unsigned short      U16;
typedef int                 S32;
typedef unsigned int        U32;
typedef long long           S64;
typedef unsigned long long  U64;
#endif

typedef int SOCKET;

inline bool InitSocket(){return true;}

inline void UninitSocket(){}

#endif

std::string ErrorMsg(int error_no);

//把IPv4地址与字符串的转化
U32 IPv4FromStr(std::string ip,bool hostByteOrder = true);

std::string IPv4String(U32 ip,bool hostByteOrder = true);

#endif
