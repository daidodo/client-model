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

template<typename T1,typename T2>
bool __FromInteger(T1 & mem,T2 v){
    mem = T1(v);
    return true;
    //const T2 MAX = T2(std::numeric_limits<T1>::max());
    //const T2 MIN = T2(std::numeric_limits<T1>::min());
    //return (MIN <= v && v <= MAX);
}

template<typename T1,typename T2>
bool __ToInteger(T1 & res,T2 mem){
    res = T1(mem);
    return true;
    //const T2 MAX = T2(std::numeric_limits<T1>::max());
    //const T2 MIN = T2(std::numeric_limits<T1>::min());
    //return (MIN <= mem && mem <= MAX);
}

struct CValue
{
    int type_;
    union{
        int prog_arg_;  //program argument
        int int_;
        long long_;
        U8  u8_;
        S8  s8_;
        U16 u16_;
        S16 s16_;
        U32 u32_;
        S32 s32_;
        U64 u64_;
        S64 s64_;
    };
    std::string str_;   //STR
                        //RAW
    CSharedPtr<CTcp> tcp_;
    CSharedPtr<CUdp> udp_;
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
            case 1:return __ToInteger(res,int_);
            case 2:return __ToInteger(res,long_);
            case 3:return __ToInteger(res,u8_);
            case 4:return __ToInteger(res,s8_);
            case 5:return __ToInteger(res,u16_);
            case 6:return __ToInteger(res,s16_);
            case 7:return __ToInteger(res,u32_);
            case 8:return __ToInteger(res,s32_);
            case 9:return __ToInteger(res,u64_);
            case 10:return __ToInteger(res,s64_);
        }
        return false;
    }
    template<typename T>
    bool FromInteger(T v){
        switch(type_){
            case 1:return __FromInteger(int_,v);
            case 2:return __FromInteger(long_,v);
            case 3:return __FromInteger(u8_,v);
            case 4:return __FromInteger(s8_,v);
            case 5:return __FromInteger(u16_,v);
            case 6:return __FromInteger(s16_,v);
            case 7:return __FromInteger(u32_,v);
            case 8:return __FromInteger(s32_,v);
            case 9:return __FromInteger(u64_,v);
            case 10:return __FromInteger(s64_,v);
        }
        return false;
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

#endif
