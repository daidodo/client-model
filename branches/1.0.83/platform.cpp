#include "platform.h"

#include <sstream>
#include <iostream>

#ifdef WIN32

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

#else

std::string ErrorMsg(int error_no)
{
    const int MAX_BUF = 256;
    char buf[MAX_BUF];
    std::ostringstream os;
    os<<" errno="<<error_no<<" - "<<strerror_r(error_no,buf,MAX_BUF);
    return os.str();
}

#endif
