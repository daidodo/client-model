#include <sstream>
#include "rt_structs.h"
#include "util.h"
#include "errors.h"

//CTcp
CTcp::CTcp(int ln)
    : lineno_(ln)
    , timeMs_(30000)
{}

//CUdp
CUdp::CUdp(int ln)
    : lineno_(ln)
    , timeMs_(30000)
{}

//CValue
CValue::CValue()
    : type_(0)
    , u64_(0)
{}

std::string CValue::ToString() const
{
    std::ostringstream oss;
    oss<<"(type_="<<type_;
    switch(type_){
        case 1:oss<<",int_="<<int_;break;
        case 2:oss<<",long_="<<long_;break;
        case 3:oss<<",u8_="<<u8_;break;
        case 4:oss<<",s8_="<<s8_;break;
        case 5:oss<<",u16_="<<u16_;break;
        case 6:oss<<",s16_="<<s16_;break;
        case 7:oss<<",u32_="<<u32_;break;
        case 8:oss<<",s32_="<<s32_;break;
        case 9:oss<<",u64_="<<u64_;break;
        case 10:oss<<",s64_="<<s64_;break;
        case 11:oss<<",str_="<<str_;break;
        case 12:oss<<",tcp_="<<to_str(tcp_);break;
        case 13:oss<<",udp_="<<to_str(udp_);break;
        case 14:oss<<",raw_="<<str_;break;
    }
    oss<<")";
    return oss.str();
}

std::string CValue::ShowValue(bool hasLen) const
{
    std::ostringstream oss;
    switch(type_){
        case 1:oss<<int_;break;
        case 2:oss<<long_;break;
        case 3:oss<<U32(u8_);break;
        case 4:oss<<S32(s8_);break;
        case 5:oss<<u16_;break;
        case 6:oss<<s16_;break;
        case 7:oss<<u32_;break;
        case 8:oss<<s32_;break;
        case 9:oss<<u64_;break;
        case 10:oss<<s64_;break;
        case 11:case 14:oss<<Dump(str_,-1,hasLen);break;
        case 12:oss<<tcp_->ToString();break;
        case 13:oss<<udp_->ToString();break;
    }
    return oss.str();
}

bool CValue::IsSigned(int type){
    return (type == 1 ||
        type == 2 ||
        type == 4 ||
        type == 6 ||
        type == 8 ||
        type == 10);
}

bool CValue::IsUnsigned(int type){
    return (type == 3 ||
        type == 5 ||
        type == 7 ||
        type == 9);
}

void CValue::FixRaw()
{
    assert(IsString());
    type_ = 14;
}

int CValue::operator <(const CValue & v) const
{
    if(IsString()){
        assert(v.IsString());
        return (str_ < v.str_ ? 1 : 0);
    }else if(IsInteger()){
        assert(v.IsInteger());
        if(IsSigned()){
            S64 v1 = 0;
            ToInteger(v1);
            if(v.IsSigned()){
                S64 v2 = 0;
                v.ToInteger(v2);
                return (v1 < v2 ? 1 : 0);
            }else{
                if(v1 < 0)
                    return -1;
                U64 v2 = 0;
                v.ToInteger(v2);
                return (v1 < v2 ? 1 : 0);
            }
        }else{
            U64 v1 = 0;
            ToInteger(v1);
            if(v.IsSigned()){
                S64 v2 = 0;
                v.ToInteger(v2);
                if(v2 < 0)
                    return -1;
                return (v1 < v2 ? 1 : 0);
            }else{
                U64 v2 = 0;
                v.ToInteger(v2);
                return (v1 < v2 ? 1 : 0);
            }
        }
    }
    return -2;
}

int CValue::operator <=(const CValue & v) const
{
    int ret = operator >(v);
    return (ret == 0 ? 1 : (ret == 1 ? 0 : ret));
}

int CValue::operator >=(const CValue & v) const
{
    int ret = operator <(v);
    return (ret == 0 ? 1 : (ret == 1 ? 0 : ret));
}

int CValue::operator ==(const CValue & v) const
{
    if(IsString()){
        assert(v.IsString());
        return (str_ == v.str_ ? 1 : 0);
    }else if(IsInteger()){
        assert(v.IsInteger());
        if(IsSigned()){
            S64 v1 = 0;
            ToInteger(v1);
            if(v.IsSigned()){
                S64 v2 = 0;
                v.ToInteger(v2);
                return (v1 == v2 ? 1 : 0);
            }else{
                if(v1 < 0)
                    return -1;
                U64 v2 = 0;
                v.ToInteger(v2);
                return (v1 == v2 ? 1 : 0);
            }
        }else{
            U64 v1 = 0;
            ToInteger(v1);
            if(v.IsSigned()){
                S64 v2 = 0;
                v.ToInteger(v2);
                if(v2 < 0)
                    return -1;
                return (v1 == v2 ? 1 : 0);
            }else{
                U64 v2 = 0;
                v.ToInteger(v2);
                return (v1 == v2 ? 1 : 0);
            }
        }
    }
    return -2;
}

int CValue::operator !=(const CValue & v) const
{
    int ret = operator ==(v);
    return (ret == 0 ? 1 : (ret == 1 ? 0 : ret));
}

int CValue::operator !() const
{
    assert(IsInteger());
    if(IsSigned()){
        S64 v1 = 0;
        ToInteger(v1);
        return (v1 == 0 ? 1 : 0);
    }else{
        U64 v1 = 0;
        ToInteger(v1);
        return (v1 == 0 ? 1 : 0);
    }
}

bool CValue::StreamOut(const CValue & v,int lineno)
{
    if(!IsString()){
        RUNTIME_ERR(lineno,"invalid left hand type for stream-out operator");
        return false;
    }
    if(v.IsString()){
        str_ = v.str_;
        return true;
    }
    std::ostringstream oss;
    switch(v.type_){
        case 1:oss<<v.int_;break;
        case 2:oss<<v.long_;break;
        case 3:oss<<v.u8_;break;
        case 4:oss<<v.s8_;break;
        case 5:oss<<v.u16_;break;
        case 6:oss<<v.s16_;break;
        case 7:oss<<v.u32_;break;
        case 8:oss<<v.s32_;break;
        case 9:oss<<v.u64_;break;
        case 10:oss<<v.s64_;break;
        default:{
            RUNTIME_ERR(lineno,"invalid right hand type for stream-out operator");
            return false;
        }
    }
    str_ = oss.str();
    return true;
}

CSharedPtr<CValue> CValue::Copy() const
{
    CSharedPtr<CValue> ret = New<CValue>();
    *ret = *this;
    return ret;
}

COutByteStream & operator <<(COutByteStream & ds,const CValue & v)
{
    switch(v.type_){
        case 3:ds<<v.u8_;break;
        case 4:ds<<v.s8_;break;
        case 5:ds<<v.u16_;break;
        case 6:ds<<v.s16_;break;
        case 7:ds<<v.u32_;break;
        case 8:ds<<v.s32_;break;
        case 9:ds<<v.u64_;break;
        case 10:ds<<v.s64_;break;
        case 11:ds<<v.str_;break;
        case 14:ds<<Manip::raw(v.str_.c_str(),v.str_.length());break;
        default:ds.Status(2);
    }
    return ds;
}

CInByteStream & operator >>(CInByteStream & ds,CValue & v)
{
    switch(v.type_){
        case 3:ds>>v.u8_;break;
        case 4:ds>>v.s8_;break;
        case 5:ds>>v.u16_;break;
        case 6:ds>>v.s16_;break;
        case 7:ds>>v.u32_;break;
        case 8:ds>>v.s32_;break;
        case 9:ds>>v.u64_;break;
        case 10:ds>>v.s64_;break;
        case 11:ds>>v.str_;break;
        default:ds.Status(2);
    }
    return ds;
}
