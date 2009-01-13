#include "platform.h"

#include <sstream>
#include <iostream>

#ifdef WIN32

bool InitSocket(){
    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(wVersionRequested,&wsaData) != 0)
        return false;
    if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2 ){
        WSACleanup();
        return false; 
    }
    return true;
}

void sleep(unsigned int sec)
{
    DWORD MSec = sec * 1000;
    Sleep(MSec);
}

std::string ErrorMsg(int error_no)
{
    std::ostringstream oss;
    oss<<" errno="<<error_no;
    TCHAR msg[512] = {0};
    if(FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        0,
        error_no,
        MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),  //Default language
        msg,
        1024,
        0))
    {
        oss<<", "<<msg;
    }
    return oss.str();
}

U32 IPv4FromStr(std::string ip,bool hostByteOrder)
{
    U32 ret = inet_addr(ip.c_str());
    return hostByteOrder ? ntohl(ret) : ret;	
}

std::string IPv4String(U32 ip,bool hostByteOrder)
{
    struct in_addr in;
    in.s_addr = hostByteOrder ? htonl(ip) : ip;
    char * ret = inet_ntoa(in);
    return (ret ? ret : "ERROR_IP");
}


#else

std::string ErrorMsg(int error_no)
{
    const int MAX_BUF = 256;
    char buf[MAX_BUF];
    std::ostringstream os;
    os<<" errno="<<error_no<<" - "<<strerror_r(error_no,buf,MAX_BUF);
    return os.str();
}

U32 IPv4FromStr(std::string ip,bool hostByteOrder)
{
    struct in_addr in;
    if(inet_pton(AF_INET,ip.c_str(),&in) == 0)
        return 0;
    return hostByteOrder ? ntohl(in.s_addr) : in.s_addr;	
}

std::string IPv4String(U32 ip,bool hostByteOrder)
{
    struct in_addr in;
    in.s_addr = hostByteOrder ? htonl(ip) : ip;
    char buf[46];
    if(!inet_ntop(AF_INET,&in,buf,sizeof buf))
        return "ERROR_IP";
    return buf;
}


#endif
