#ifndef DOZERG_UTILITY_H_20081111
#define DOZERG_UTILITY_H_20081111

#include <string>

int str2int(const char * str,size_t len);

int atoi_base8(const char * str,size_t len);

int atoi_base16(const char * str,size_t len);

template<class T>
std::string to_str(const T * p){
    return (p ? p->ToString() : "0x0");
}

template<class T>
std::string signa(const T * p){
    return (p ? p->Signature() : "0x0");
}

#endif
