#include "rt_structs.h"
#include "errors.h"

//CTcp
CTcp::CTcp(int ln)
    : lineno_(ln)
    , timeMs_(0)
{}

//CUdp
CUdp::CUdp(int ln)
    : lineno_(ln)
    , timeMs_(0)
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
        case DT_INT:oss<<",int_="<<int_;break;
        case DT_LONG:oss<<",long_="<<long_;break;
        case DT_U8:oss<<",u8_="<<u8_;break;
        case DT_S8:oss<<",s8_="<<s8_;break;
        case DT_U16:oss<<",u16_="<<u16_;break;
        case DT_S16:oss<<",s16_="<<s16_;break;
        case DT_U32:oss<<",u32_="<<u32_;break;
        case DT_S32:oss<<",s32_="<<s32_;break;
        case DT_U64:oss<<",u64_="<<u64_;break;
        case DT_S64:oss<<",s64_="<<s64_;break;
        case DT_STR:oss<<",str_="<<str_;break;
        case DT_RAW:oss<<",raw_="<<str_;break;
        case DT_TCP:oss<<",tcp_="<<to_str(tcp_);break;
        case DT_UDP:oss<<",udp_="<<to_str(udp_);break;
        case DT_PA:oss<<",prog_arg_="<<str_;break;
    }
    oss<<")";
    return oss.str();
}

std::string CValue::ShowValue(bool hasLen) const
{
    std::ostringstream oss;
    switch(type_){
        case DT_INT:oss<<int_;break;
        case DT_LONG:oss<<long_;break;
        case DT_U8:oss<<U32(u8_);break;
        case DT_S8:oss<<S32(s8_);break;
        case DT_U16:oss<<u16_;break;
        case DT_S16:oss<<s16_;break;
        case DT_U32:oss<<u32_;break;
        case DT_S32:oss<<s32_;break;
        case DT_U64:oss<<u64_;break;
        case DT_S64:oss<<s64_;break;
        case DT_STR:case DT_RAW:oss<<Dump(str_,size_t(-1),hasLen);break;
        case DT_TCP:oss<<tcp_->ToString();break;
        case DT_UDP:oss<<udp_->ToString();break;
        case DT_PA:return str_;
    }
    return oss.str();
}

void CValue::FixRaw()
{
    assert(IsString());
    type_ = DT_RAW;
}

int CValue::operator <(const CValue & v) const
{
    if(IsString()){
        assert(v.IsString());
        return (str_ < v.str_ ? RET_TRUE : RET_FALSE);
    }else if(IsInteger()){
        assert(v.IsInteger());
        if(IsSigned()){
            S64 v1 = 0;
            ToInteger(v1);
            if(v.IsSigned()){
                S64 v2 = 0;
                v.ToInteger(v2);
                return (v1 < v2 ? RET_TRUE : RET_FALSE);
            }else{
                if(v1 < 0)
                    return RET_SIGN_MISMATCH;
                U64 v2 = 0;
                v.ToInteger(v2);
                return (U64(v1) < v2 ? RET_TRUE : RET_FALSE);
            }
        }else{
            U64 v1 = 0;
            ToInteger(v1);
            if(v.IsSigned()){
                S64 v2 = 0;
                v.ToInteger(v2);
                if(v2 < 0)
                    return RET_SIGN_MISMATCH;
                return (v1 < U64(v2) ? RET_TRUE : RET_FALSE);
            }else{
                U64 v2 = 0;
                v.ToInteger(v2);
                return (v1 < v2 ? RET_TRUE : RET_FALSE);
            }
        }
    }
    return RET_TYPE_ERROR;
}

int CValue::operator <=(const CValue & v) const
{
    int ret = operator >(v);
    return (ret == RET_FALSE ? RET_TRUE : (ret == RET_TRUE ? RET_FALSE : ret));
}

int CValue::operator >=(const CValue & v) const
{
    int ret = operator <(v);
    return (ret == RET_FALSE ? RET_TRUE : (ret == RET_TRUE ? RET_FALSE : ret));
}

int CValue::operator ==(const CValue & v) const
{
    if(IsString()){
        assert(v.IsString());
        return (str_ == v.str_ ? RET_TRUE : RET_FALSE);
    }else if(IsInteger()){
        assert(v.IsInteger());
        if(IsSigned()){
            S64 v1 = 0;
            ToInteger(v1);
            if(v.IsSigned()){
                S64 v2 = 0;
                v.ToInteger(v2);
                return (v1 == v2 ? RET_TRUE : RET_FALSE);
            }else{
                if(v1 < 0)
                    return RET_SIGN_MISMATCH;
                U64 v2 = 0;
                v.ToInteger(v2);
                return (v1 == v2 ? RET_TRUE : RET_FALSE);
            }
        }else{
            U64 v1 = 0;
            ToInteger(v1);
            if(v.IsSigned()){
                S64 v2 = 0;
                v.ToInteger(v2);
                if(v2 < 0)
                    return RET_SIGN_MISMATCH;
                return (v1 == v2 ? RET_TRUE : RET_FALSE);
            }else{
                U64 v2 = 0;
                v.ToInteger(v2);
                return (v1 == v2 ? RET_TRUE : RET_FALSE);
            }
        }
    }
    return RET_TYPE_ERROR;
}

int CValue::operator !=(const CValue & v) const
{
    int ret = operator ==(v);
    return (ret == RET_FALSE ? RET_TRUE : (ret == RET_TRUE ? RET_FALSE : ret));
}

int CValue::operator !() const
{
    assert(IsInteger());
    if(IsSigned()){
        S64 v1 = 0;
        ToInteger(v1);
        return (v1 == 0 ? RET_TRUE : RET_FALSE);
    }else{
        U64 v1 = 0;
        ToInteger(v1);
        return (v1 == 0 ? RET_TRUE : RET_FALSE);
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
        case DT_INT:oss<<v.int_;break;
        case DT_LONG:oss<<v.long_;break;
        case DT_U8:oss<<v.u8_;break;
        case DT_S8:oss<<v.s8_;break;
        case DT_U16:oss<<v.u16_;break;
        case DT_S16:oss<<v.s16_;break;
        case DT_U32:oss<<v.u32_;break;
        case DT_S32:oss<<v.s32_;break;
        case DT_U64:oss<<v.u64_;break;
        case DT_S64:oss<<v.s64_;break;
        default:{
            RUNTIME_ERR(lineno,"invalid right hand type for stream-out operator");
            return false;
        }
    }
    str_ = oss.str();
    return true;
}

COutByteStream & operator <<(COutByteStream & ds,const CValue & v)
{
    switch(v.type_){
        case DT_U8:ds<<v.u8_;break;
        case DT_S8:ds<<v.s8_;break;
        case DT_U16:ds<<v.u16_;break;
        case DT_S16:ds<<v.s16_;break;
        case DT_U32:ds<<v.u32_;break;
        case DT_S32:ds<<v.s32_;break;
        case DT_U64:ds<<v.u64_;break;
        case DT_S64:ds<<v.s64_;break;
        case DT_STR:ds<<v.str_;break;
        case DT_RAW:ds<<Manip::raw(v.str_.c_str(),v.str_.length());break;
        default:ds.Status(2);
    }
    return ds;
}

CInByteStream & operator >>(CInByteStream & ds,CValue & v)
{
    switch(v.type_){
        case DT_U8:ds>>v.u8_;break;
        case DT_S8:ds>>v.s8_;break;
        case DT_U16:ds>>v.u16_;break;
        case DT_S16:ds>>v.s16_;break;
        case DT_U32:ds>>v.u32_;break;
        case DT_S32:ds>>v.s32_;break;
        case DT_U64:ds>>v.u64_;break;
        case DT_S64:ds>>v.s64_;break;
        case DT_STR:ds>>v.str_;break;
        default:ds.Status(2);
    }
    return ds;
}

