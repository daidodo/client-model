#include <sstream>
#include "rt_structs.h"
#include "util.h"
#include "errors.h"

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

std::string CValue::Signature() const
{
    return ToString();
}

void CValue::FixRaw()
{
    assert(IsString());
    type_ = 14;
}

bool CValue::operator <(const CValue & v) const
{
    assert(IsInteger() && v.IsInteger());
    if(!IsInteger()){



    }
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
        default:ds.Status(1);
    }
    return ds;
}

