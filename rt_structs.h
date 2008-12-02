#ifndef DOZERG_RUNTIME_STRUCTS_H_20081117
#define DOZERG_RUNTIME_STRUCTS_H_20081117

#include <cassert>
#include <limits>
#include "common/Sockets.h"
#include "common/SharedPtr.h"
#include "common/DataStream.h"

struct CTcp : public CTcpConnSocket
{
    const int lineno_;
    U32 timeMs_;       //send/recv timeout
    //functions:
    explicit CTcp(int ln);
};

struct CUdp : public CUdpSocket
{
    const int lineno_;
    U32 timeMs_;       //send/recv timeout
    //functions:
    explicit CUdp(int ln);
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
    std::string str_;   //11  STR
                        //14  RAW
    CSharedPtr<CTcp> tcp_;  //12
    CSharedPtr<CUdp> udp_;  //13
    //functions:
    CValue();
    std::string ToString() const;
    std::string Signature() const{return ToString();}
    std::string ShowValue(bool hasLen = true) const;
    static bool IsVoid(int type){return type == 0;}
    static bool IsConnection(int type){return type == 12 || type == 13;}
    static bool IsTcp(int type){return type == 12;}
    static bool IsUdp(int type){return type == 13;}
    static bool IsInteger(int type){return type >= 1 && type <= 10;}
    static bool IsSigned(int type);
    static bool IsUnsigned(int type);
    static bool IsString(int type){return type == 11 || type == 14;}
    static bool IsRaw(int type){return type == 14;}
    bool IsConnection() const{return IsConnection(type_);}
    bool IsTcp() const{return IsTcp(type_);}
    bool IsUdp() const{return IsUdp(type_);}
    bool IsInteger() const{return IsInteger(type_);}
    bool IsSigned() const{return IsSigned(type_);}
    bool IsUnsigned() const{return IsUnsigned(type_);}
    bool IsString() const{return IsString(type_);}
    bool IsRaw() const{return IsRaw(type_);}
    void FixRaw();
    template<typename T>
    bool ToInteger(T & res) const{
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
    /*  return :
        0   assert false
        1   assert true
        -1  signed, unsigned mismatch
        -2  argument type error
    //*/
    int operator <(const CValue & v) const;
    int operator >(const CValue & v) const{return v.operator <(*this);}
    int operator <=(const CValue & v) const;
    int operator >=(const CValue & v) const;
    int operator ==(const CValue & v) const;
    int operator !=(const CValue & v) const;
    int operator !() const;
    bool StreamOut(const CValue & v,int lineno);
private:
    template<typename T>
    bool operator <(T v) const{
        return true;
    }
 };

COutByteStream & operator <<(COutByteStream & ds,const CValue & v);

CInByteStream & operator >>(CInByteStream & ds,CValue & v);

#undef __FROM_INTEGER
#undef __TO_INTEGER

#endif
