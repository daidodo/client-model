#include "platform.h"

#include <sstream>
#include <iostream>

#ifdef WIN32

std::string ErrorMsg(int error_no)
{
    std::ostringstream os;
    os<<" errno="<<error_no;
    return os.str();
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
