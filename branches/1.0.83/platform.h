#ifndef DOZERG_PLATFORM_H_20090105
#define DOZERG_PLATFORM_H_20090105

#include <string>
#include "types.h"

#ifdef WIN32

#   include <Winsock2.h>
#   include <Ws2def.h>
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

typedef int SOCKET;

inline bool InitSocket(){return true;}

inline void UninitSocket(){}

#endif

std::string ErrorMsg(int error_no);


#endif
