#ifndef DOZERG_SYMBOLS_H_20081111
#define DOZERG_SYMBOLS_H_20081111

#include <vector>
#include <string>
#include <algorithm>
#include "types.h"
#include "mm.h"

struct CFixValue
{
    int type_;
    union{
        int number_;
        size_t strIdx_;
    };
};

struct CTcp
{
};

struct CUdp
{
};

struct CValue
{
    union{
        U8  u8_;
        S8  s8_;
        U16 u16_;
        S16 s16_;
        U32 u32_;
        S32 s32_;
        U64 u64_;
        S64 s64_;
        size_t strIdx_;
        CTcp * tcp_;
        CUdp * udp_;
    };
};

struct CArrayType;

struct CVariable
{
    std::string varname_;
    int type_;
    union{
        int simple_type_;
        CArrayType * array_type_;
    };
    std::vector<CValue> val_;
    //functions:
    ~CVariable(){
        if(type_ == 2)
            Delete(array_type_);
    }
};

struct CFuncCall;

struct CExpr
{
    int type_;
    union{
        CFixValue * fix_value_;
        CFuncCall * func_call_;
        CVariable * var_;
    };
    //functions:
    ~CExpr(){
        switch(type_){
            case 1:Delete(fix_value_);break;
            case 2:Delete(func_call_);break;
            case 3:Delete(var_);break;
            default:;
        }
    }
};

struct CArrayType
{
    int simple_type_;
    CExpr * expr_;
    //functions:
    ~CArrayType(){
        if(expr_){
            Delete(expr_);
        }
    }
};

struct CAssertExp
{
    int op_token_;
    CExpr * expr1_;
    CExpr * expr2_;
    //functions:
    ~CAssertExp(){
        Delete(expr1_);
        if(expr2_)
            Delete(expr2_);
    }
};

struct CSimDeclare
{
    int type_;
    CVariable * var_;
    int op_token;
    union{
        CExpr * expr_;
        int simple_type;
    };
    //functions:
    ~CSimDeclare(){
        Delete(var_);
        switch(type_){
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:Delete(expr_);break;
            default:;
        }
    }
};

typedef std::vector<CExpr *> __ArgList;

struct CFuncCall
{
    int type_;
    union{
        int func_name_;
        int simple_type_;
    };
    __ArgList * arg_list_;
    //functions:
    ~CFuncCall(){
        if(arg_list_){
            std::for_each(arg_list_->begin(),arg_list_->end(),Delete<CExpr>);
            Delete(arg_list_);
        }
    }
};

struct CStmt
{
    int type_;
    union{
        CAssertExp * assert_;
        CSimDeclare * declare_;
        CFuncCall * func_call_;
    };
    //functions:
    ~CStmt(){
        switch(type_){
            case 1:Delete(assert_);break;
            case 2:Delete(declare_);break;
            case 3:Delete(func_call_);break;
            default:;
        }
    }
};

struct CCommand
{
    std::string cmd_name_;
    std::vector<CStmt *> items_;
    //functions:
    ~CCommand(){
        std::for_each(items_.begin(),items_.end(),Delete<CStmt>);
    }
};

#endif
