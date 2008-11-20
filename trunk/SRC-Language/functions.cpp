#include <limits>
#include "mm.h"
#include "errors.h"
#include "util.h"
#include "functions.h"

template<typename T>
static void IntegerCtor(const std::vector<__ValuePtr> & args,int lineno,
                              T & res,const char * type_str)
{
    assert(args.size() < 2);
    if(args.empty())
        return;
    __ValuePtr arg = args[0];
    const T MIN = std::numeric_limits<T>::min();
    const T MAX = std::numeric_limits<T>::max();
    switch(arg->type_){
        case 1:{    //int_
            if(arg->int_ < MIN || arg->int_ > MAX){
                GAMMAR_ERR(lineno,"invalid value for "<<type_str);
            }
            res = arg->int_;
            break;}
        case 2:{    //long_
            if(arg->long_ < MIN || arg->long_ > MAX){
                GAMMAR_ERR(lineno,"invalid conversion from long to "<<type_str);
            }
            res = arg->long_;
            break;}
        case 3:{    //u8_
            if(arg->u8_ < MIN || arg->u8_ > MAX){
                GAMMAR_ERR(lineno,"invalid conversion from U8 to "<<type_str);
            }
            res = arg->u8_;
            break;}
        case 4:{    //s8_
            if(arg->s8_ < MIN || arg->s8_ > MAX){
                GAMMAR_ERR(lineno,"invalid conversion from S8 to "<<type_str);
            }
            res = arg->s8_;
            break;}
        case 5:{    //u16_
            if(arg->u16_ < MIN || arg->u16_ > MAX){
                GAMMAR_ERR(lineno,"invalid conversion from U16 to "<<type_str);
            }
            res = arg->u16_;
            break;}
        case 6:{    //s16_
            if(arg->s16_ < MIN || arg->s16_ > MAX){
                GAMMAR_ERR(lineno,"invalid conversion from U16 to "<<type_str);
            }
            res = arg->s16_;
            break;}
        case 7:{    //u32_
            if(arg->u32_ < MIN || arg->u32_ > MAX){
                GAMMAR_ERR(lineno,"invalid conversion from U16 to "<<type_str);
            }
            res = arg->u32_;
            break;}
        case 8:{    //s32_
            break;}
            if(arg->s32_ < MIN || arg->s32_ > MAX){
                GAMMAR_ERR(lineno,"invalid conversion from U16 to "<<type_str);
            }
            res = arg->s32_;
        case 9:{    //u64_
            if(arg->u64_ < MIN || arg->u64_ > MAX){
                GAMMAR_ERR(lineno,"invalid conversion from U16 to "<<type_str);
            }
            res = arg->u64_;
            break;}
        case 10:{   //s64_
            if(arg->s64_ < MIN || arg->s64_ > MAX){
                GAMMAR_ERR(lineno,"invalid conversion from U16 to "<<type_str);
            }
            res = arg->s64_;
            break;}
        default:{
            GAMMAR_ERR(lineno,"invalid conversion to "<<type_str);
        }
    }
}

__ValuePtr EvaluateU8(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 3;
    IntegerCtor(args,lineno,ret->u8_,"U8");
    return ret;
}

__ValuePtr EvaluateS8(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 4;
    IntegerCtor(args,lineno,ret->s8_,"S8");
    return ret;
}

__ValuePtr EvaluateU16(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 5;
    IntegerCtor(args,lineno,ret->u16_,"U16");
    return ret;
}

__ValuePtr EvaluateS16(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 6;
    IntegerCtor(args,lineno,ret->s16_,"S16");
    return ret;
}

__ValuePtr EvaluateU32(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 7;
    IntegerCtor(args,lineno,ret->u32_,"U32");
    return ret;
}

__ValuePtr EvaluateS32(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 8;
    IntegerCtor(args,lineno,ret->s32_,"S32");
    return ret;
}


__ValuePtr EvaluateU64(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 9;
    IntegerCtor(args,lineno,ret->u64_,"U64");
    return ret;
}

__ValuePtr EvaluateS64(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 10;
    IntegerCtor(args,lineno,ret->s64_,"S64");
    return ret;
}

__ValuePtr EvaluateSTR(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 11;
    if(!args.empty()){
        if(args[0]->type_ != 11){
            GAMMAR_ERR(lineno,"invalid conversion to STR");
        }else
            ret->str_ = args[0]->str_;
    }
    return ret;
}
__ValuePtr EvaluateRAW(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 11;
    if(!args.empty()){
        if(args[0]->type_ != 11){
            GAMMAR_ERR(lineno,"invalid conversion to RAW");
        }else
            ret->str_ = args[0]->str_;
    }
    return ret;
}

__ValuePtr EvaluateTCP(const std::vector<__ValuePtr> & args,int lineno)
{
    if(args.size() == 1){
        if(args[0]->type_ == 12)
            return args[0];
        GAMMAR_ERR(lineno,"invalid conversion to TCP");
    }else if(args.size() == 2){
        assert(args[0]->type_ == 11);   //string
        __ValuePtr ret = New<CValue>();
        ret->type_ = 12;




        return ret;
    }
    return 0;
}
__ValuePtr EvaluateUDP(const std::vector<__ValuePtr> & args,int lineno)
{
    if(args.size() == 1){
        if(args[0]->type_ == 13)
            return args[0];
        GAMMAR_ERR(lineno,"invalid conversion to TCP");
    }else if(args.size() == 2){
        assert(args[0]->type_ == 11);   //string
        __ValuePtr ret = New<CValue>();
        ret->type_ = 13;




        return ret;
    }
    return 0;
}

__ValuePtr EvaluateHEX(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 11;
    if(!args.empty()){
        if(args[0]->type_ != 11){
            GAMMAR_ERR(lineno,"invalid conversion to RAW");
        }else
            ret->str_ = DumpHex(args[0]->str_);
    }
    return ret;
}
__ValuePtr EvaluateUNHEX(const std::vector<__ValuePtr> & args,int lineno)
{
    __ValuePtr ret = New<CValue>();
    ret->type_ = 11;
    if(!args.empty()){
        if(args[0]->type_ != 11){
            GAMMAR_ERR(lineno,"invalid conversion to RAW");
        }else
            ret->str_ = UnHex(args[0]->str_);
    }
    return ret;
}