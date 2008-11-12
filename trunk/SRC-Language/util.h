#ifndef DOZERG_UTILITY_H_20081111
#define DOZERG_UTILITY_H_20081111

#include <string>

int str2int(const char * str,size_t len);

///*  return: 
//        -n  error
//        0
//        +n  # of '\n'
////*/
//int qstr(std::string & ret,const char * src,size_t len);

int atoi_base8(const char * str,size_t len);

int atoi_base16(const char * str,size_t len);

#endif
