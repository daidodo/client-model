#ifndef DOZERG_RUNTIME_STRUCTS_H_20081117
#define DOZERG_RUNTIME_STRUCTS_H_20081117

#include <cassert>
#include <limits>
#include "common/Sockets.h"
#include "common/SharedPtr.h"

struct CTcp : public CTcpConnSocket
{
    const int lineno_;
    //functions:
    //explicit CTcp(int ln);
    //std::string Signature() const;
};

struct CUdp : public CUdpSocket
{
    const int lineno_;
    //functions:
    //explicit CUdp(int ln);
    //std::string Signature() const;
};

#define __FROM_INTEGER(T,mem,v) {   \
        mem = v;   \
        const T MAX = std::numeric_limits<T>::max();  \
        const T MIN = std::numeric_limits<T>::min();  \
        if(v < MIN || v > MAX)  \
            return false;   \
    }

#define __TO_INTEGER(T,res,mem) {   \
        res = mem;   \
        const T MAX = std::numeric_limits<T>::max();  \
        const T MIN = std::numeric_limits<T>::min();  \
        if(mem < MIN || mem > MAX)  \
            return false;   \
    }

struct CValue
{
    int type_;
    union{
        int int_;       //1
        long long_;     //2
        U8  u8_;        //3
        S8  s8_;        //4
        U16 u16_;       //5
        S16 s16_;       //6
        U32 u32_;       //7
        S32 s32_;       //8
        U64 u64_;       //9
        S64 s64_;       //10
    };
    std::string str_;   //11
    CSharedPtr<CTcp> tcp_;  //12
    CSharedPtr<CUdp> udp_;  //13
    //functions:
    CValue();
    std::string ToString() const;
    std::string Signature() const;
    bool IsConnection() const{return type_ == 12 || type_ == 13;}
    bool IsInteger() const{return type_ >= 1 && type_ <= 10;}
    template<typename T>
    bool ToInteger(T & res){
        switch(type_){
            case 1:__TO_INTEGER(int,res,int_);break;
            case 2:__TO_INTEGER(long,res,long_);break;
            case 3:__TO_INTEGER(U8,res,u8_);break;
            case 4:__TO_INTEGER(S8,res,s8_);break;
            case 5:__TO_INTEGER(U16,res,u16_);break;
            case 6:__TO_INTEGER(S16,res,s16_);break;
            case 7:__TO_INTEGER(U32,res,u32_);break;
            case 8:__TO_INTEGER(S32,res,s32_);break;
            case 9:__TO_INTEGER(U64,res,u64_);break;
            case 10:__TO_INTEGER(S64,res,s64_);break;
            default:
                return false;
        }
        return true;
    }
    template<typename T>
    bool FromInteger(T v){
        switch(type_){
            case 1:__FROM_INTEGER(int,int_,v);break;
            case 2:__FROM_INTEGER(long,long_,v);break;
            case 3:__FROM_INTEGER(U8,u8_,v);break;
            case 4:__FROM_INTEGER(S8,s8_,v);break;
            case 5:__FROM_INTEGER(U16,u16_,v);break;
            case 6:__FROM_INTEGER(S16,s16_,v);break;
            case 7:__FROM_INTEGER(U32,u32_,v);break;
            case 8:__FROM_INTEGER(S32,s32_,v);break;
            case 9:__FROM_INTEGER(U64,u64_,v);break;
            case 10:__FROM_INTEGER(S64,s64_,v);break;
            default:
                return false;
        }
        return true;
    }
 };


#undef __FROM_INTEGER
#undef __TO_INTEGER

#endif
