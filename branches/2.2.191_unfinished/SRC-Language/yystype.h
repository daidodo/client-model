#ifndef DOZERG_YYSTYPE_H_20081116
#define DOZERG_YYSTYPE_H_20081116

#include "symbols.h"

struct yystype{
    union{
        int         int_;
        long        long_;
        long long   i64_;
        size_t      strIdx_;
        int         prog_arg_;
        int         token_;
    };
    CSharedPtr<CFixValue>   fix_value_;
    CSharedPtr<CArrayValue> array_val_;
    CSharedPtr<CExpr>       expr_;
    //CSharedPtr<CVariable>   var_;
    CSharedPtr<CArgList>    arg_list_;
    CSharedPtr<CConstDecl>  constDecl_;
    CSharedPtr<CPostDecl>   postDecl_;
    CSharedPtr<CArrayDecl>  arrayDecl_;
    CSharedPtr<CAssertDecl> assertDecl_;
    CSharedPtr<CStreamDecl> streamDecl_;
    CSharedPtr<CDefineDecl> defDecl_;
    CSharedPtr<CDeclare>    declare_;
    CSharedPtr<CFuncCall>   func_call_;
    CSharedPtr<CAssertExp>  assert_exp_;
};

#define YYSTYPE yystype

extern YYSTYPE yylval;

#endif
