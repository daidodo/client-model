#ifndef DOZERG_SYMBOLS_H_20081111
#define DOZERG_SYMBOLS_H_20081111

#include <vector>

typedef const char * __Argname;

struct CFixValue        //8
{
    int type_;
    union{
        int number_;
        size_t strIdx_;
    };
};

struct CFuncCall;

struct CExpr            //8
{
    int type_;
    union{
        CFixValue * fix_value_;
        CFuncCall * func_call_;
        __Argname argname_;
    };
};

struct CSimTypeName     //8
{
    int type_token_;
    __Argname argname_;
};

struct CArrayType       //8
{
    int type_token_;
    CExpr * expr_;
};

typedef std::vector<CExpr>  __ArgList;

struct CAssertExp       //12
{
    int op_token_;
    CExpr * expr1_;
    CExpr * expr2_;
};

struct COpExpr          //8
{
    int op_token;
    CExpr * expr_;
};

struct COpSimtype       //8
{
    int op_token_;
    int type_token_;
};

struct CSimDeclare      //16
{
    int type_;
    union{
        CArrayType * array_type_;
        CSimTypeName * sim_type_name_;
    };
    union{
        __Argname argname_;
        CExpr * expr_;
        __ArgList * arg_list_;
        COpExpr op_expr_;
        COpSimtype op_simtype_;
    };
};

struct CFuncCall        //12
{
    int type_;
    int token_;
    __ArgList * arg_list_;
};

#endif
