#ifndef DOZERG_RUNTIME_STRUCTS_H_20081117
#define DOZERG_RUNTIME_STRUCTS_H_20081117

#include <cassert>
#include <limits>
#include "constants.h"
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

struct CValue
{
    int type_;
    union{
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
                        //program argument
    CSharedPtr<CTcp> tcp_;
    CSharedPtr<CUdp> udp_;
    //functions:
    CValue();
    std::string ToString() const;
    std::string Signature() const{return ToString();}
    std::string ShowValue(bool hasLen = true) const;
    bool IsConnection() const{return DT_IsConnection(type_);}
    bool IsTcp() const{return DT_IsTcp(type_);}
    bool IsUdp() const{return DT_IsUdp(type_);}
    bool IsInteger() const{return DT_IsInteger(type_);}
    bool IsSigned() const{return DT_IsSigned(type_);}
    bool IsUnsigned() const{return DT_IsUnsigned(type_);}
    bool IsString() const{return DT_IsString(type_);}
    bool IsRaw() const{return DT_IsRaw(type_);}
    bool IsProgArg() const{return DT_IsProgArg(type_);}
    bool IsStrOrPA() const{return IsString() || IsProgArg();}
    bool IsIntOrPA() const{return IsInteger() || IsProgArg();}
    void FixRaw();
    template<typename T>
    bool ToInteger(T & res) const{
        switch(type_){
            case DT_INT:return IntAssign(res,int_);
            case DT_LONG:return IntAssign(res,long_);
            case DT_U8:return IntAssign(res,u8_);
            case DT_S8:return IntAssign(res,s8_);
            case DT_U16:return IntAssign(res,u16_);
            case DT_S16:return IntAssign(res,s16_);
            case DT_U32:return IntAssign(res,u32_);
            case DT_S32:return IntAssign(res,s32_);
            case DT_U64:return IntAssign(res,u64_);
            case DT_S64:return IntAssign(res,s64_);
            case DT_PA:return IntAssign(res,str_);
        }
        return false;
    }
    template<typename T>
    bool FromInteger(T v){
        switch(type_){
            case DT_INT:return IntAssign(int_,v);
            case DT_LONG:return IntAssign(long_,v);
            case DT_U8:return IntAssign(u8_,v);
            case DT_S8:return IntAssign(s8_,v);
            case DT_U16:return IntAssign(u16_,v);
            case DT_S16:return IntAssign(s16_,v);
            case DT_U32:return IntAssign(u32_,v);
            case DT_S32:return IntAssign(s32_,v);
            case DT_U64:return IntAssign(u64_,v);
            case DT_S64:return IntAssign(s64_,v);
        }
        return false;
    }
    int operator <(const CValue & v) const;
    int operator >(const CValue & v) const{return v.operator <(*this);}
    int operator <=(const CValue & v) const;
    int operator >=(const CValue & v) const;
    int operator ==(const CValue & v) const;
    int operator !=(const CValue & v) const;
    int operator !() const;
    bool StreamOut(const CValue & v,int lineno);
 };

COutByteStream & operator <<(COutByteStream & ds,const CValue & v);

CInByteStream & operator >>(CInByteStream & ds,CValue & v);

#endif
