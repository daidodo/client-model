#ifndef DOZERG_SYMBOLS_H_20081111
#define DOZERG_SYMBOLS_H_20081111

#include <vector>
#include <string>
#include "types.h"
#include "mm.h"

struct CFixValue        //8
{
    int type_;
    union{
        int number_;
        size_t strIdx_;
    };
};

struct CTcp;
struct CUdp;

struct CValue           //8
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

struct CArg             //16
{
    std::string argname_;
    int type_;
    union{
        int simple_type_;
        CArrayType * array_type_;
    };
    std::vector<CValue> val_;
};

struct CFuncCall;

struct CExpr            //8
{
    int type_;
    union{
        CFixValue * fix_value_;
        CFuncCall * func_call_;
        CArg *      arg_;
    };
};

struct CArrayType       //8
{
    int simple_type;
    CExpr * expr_;
};

typedef std::vector<CExpr>  __ArgList;

struct CAssertExp       //12
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

struct CSimDeclare      //16
{
    int type_;
    CArg * arg_;
    int op_token;
    union{
        CExpr * expr_;
        int simple_type;
    };
    //functions:
    ~CSimDeclare(){
        Delete(arg_);
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

struct CFuncCall        //12
{
    int type_;
    union{
        int func_name_;
        int simple_type_;
    };
    __ArgList * arg_list_;
    //functions:
    ~CFuncCall(){
        Delete(arg_list_);
    }
};

struct CCmdItem
{
    int type_;
    union{
        CAssertExp * assert_;
        CSimDeclare * declare_;
        CFuncCall * func_call_;
    };
    //functions:
    ~CCmdItem(){
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
    std::vector<CCmdItem> items_;
};

struct CTcp
{
};

struct CUdp
{
};

#endif
