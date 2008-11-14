%{
#include <cassert>
#include <iostream>
#include "global.h"
#include "tokens.h"
#include "errors.h"
#include "mm.h"
#include "dbg.h"
#include "util.h"

int yylex();
%}

%token NL IEQ
%token CMD DEF
%token U8 S8 U16 S16 U32 S32 U64 S64 STR RAW TCP UDP
%token FUN BEGIN_ END HBO NBO SEND RECV HEX UNHEX
%token OP_LG OP_SM OP_LEQ OP_SEQ OP_EQ OP_NEQ OP_NOT OP_IN OP_OUT
%token <number_> NUMBER
%token <strIdx_> QSTRING
%token <var_> VAR_NAME

%type <token_> simple_type func_name comp_op stream_op
%type <fix_value_> fix_value
%type <var_> sim_type_name
%type <expr_> expr
%type <array_type_> array_type
%type <arg_list_> arg_list arg_list_not_empty
%type <assert_exp_> assert_exp
%type <declare_> simple_declare declare
%type <func_call_> func_call

%union{
	int		number_;
	size_t		strIdx_;
	int		token_;
	CFixValue *	fix_value_;
	CVariable *	var_;
	CArgList *	arg_list_;
	CExpr *		expr_;
	CArrayType *	array_type_;
	CAssertExp *	assert_exp_;
	CDeclare *	declare_;
	CFuncCall *	func_call_;
}

%%
	/* top */
program : /* empty */	{DBG_YY("program 1");}
	| program program_item
			{DBG_YY("program 2");}
	;

program_item : stmt	{DBG_YY("program_item 1");}
	| cmd_define	{DBG_YY("program_item 2");}
	;

	/* level 1 */
stmt :  stmt_sep
			{DBG_YY("stmt 1");}
	| func_call_list stmt_sep
			{DBG_YY("stmt 2");}
	| declare stmt_sep
			{DBG_YY("stmt 3");}
	;

cmd_define : cmd_begin stmt_assert_list cmd_end stmt_sep
			{DBG_YY("cmd_define 1");}
	;

	/* level 2 */
func_call_list : func_call
			{DBG_YY("func_call_list 1 ");}
	| func_call_list func_call
			{DBG_YY("func_call_list 2");}
	;

stmt_assert_list : stmt
			{DBG_YY("stmt_list 1");}
	| stmt_assert_list stmt
			{DBG_YY("stmt_list 2");}
	| stmt_assert_list assert_exp
			{DBG_YY("stmt_list 3");}
	;

cmd_begin : CMD		{DBG_YY("cmd_begin 1");program().CmdBegin(0);}
	| CMD VAR_NAME	{DBG_YY("cmd_begin 2");program().CmdBegin($2);}
	;

cmd_end : END CMD	{DBG_YY("cmd_end");program().CmdEnd();}
	;

declare : simple_declare
			{
				DBG_YY("declare 1");
				DBG_YY("$1 = "<<to_str($1));
				YY_ASSERT($1);
				$$ = $1;
				DBG_YY("$$ = "<<to_str($$));
				program().AddStmt($$);
			}
	| DEF simple_declare
			{
				DBG_YY("declare 2");
				DBG_YY("$2 = "<<to_str($2));
				YY_ASSERT($2);
				$$ = $2;
				$$->is_def_ = 1;
				DBG_YY("$$ = "<<to_str($$));
				program().AddStmt($$);
			}
	;

	/* level 3 */
func_call : func_name	
			{
				DBG_YY("func_call 1");
				DBG_YY("$1 = "<<$1);
				$$ = New<CFuncCall>(LINE_NO);
				$$->ft_token_ = $1;
				DBG_YY("$$ = "<<to_str($$));
				program().AddStmt($$);
			}
	| func_name '(' arg_list ')'
			{
				DBG_YY("func_call 2");
				DBG_YY("$1 = "<<$1);
				DBG_YY("$3 = "<<to_str($3));
				YY_ASSERT($3);
				$$ = New<CFuncCall>(LINE_NO);
				$$->ft_token_ = $1;
				$$->arg_list_ = $3;
				DBG_YY("$$ = "<<to_str($$));
				program().AddStmt($$);
			}
	| simple_type '(' arg_list ')'
			{
				DBG_YY("func_call 3");
				DBG_YY("$1 = "<<$1);
				DBG_YY("$3 = "<<to_str($3));
				$$ = New<CFuncCall>(LINE_NO);
				$$->ft_token_ = $1;
				$$->arg_list_ = $3;
				DBG_YY("$$ = "<<to_str($$));
				program().AddStmt($$);
			}
	;

assert_exp : expr comp_op expr
			{
				DBG_YY("assert_exp 1");
				DBG_YY("$1 = "<<to_str($1));
				DBG_YY("$2 = "<<$2);
				DBG_YY("$3 = "<<to_str($3));
				if(!IsBinaryPredict($2)){
					GAMMAR_ERR($1->lineno_,"prediction format error");
					Delete($1);
					Delete($3);
					$$ = 0;
				}else{
					$$ = New<CAssertExp>($1->lineno_);
					$$->op_token_ = $2;
					$$->expr1_ = $1;
					$$->expr2_ = $3;
					DBG_YY("$$ = "<<to_str($$));
					program().AddStmt($$);
				}
			}
	| comp_op expr	{
				DBG_YY("assert_exp 2");
				DBG_YY("$1 = "<<$1);
				DBG_YY("$2 = "<<to_str($2));
				if(!IsUnaryPredict($1)){
					GAMMAR_ERR($2->lineno_,"prediction format error");
					Delete($2);
					$$ = 0;
				}else{
					$$ = New<CAssertExp>($2->lineno_);
					$$->op_token_ = $1;
					$$->expr1_ = $2;
					DBG_YY("$$ = "<<to_str($$));
					program().AddStmt($$);
				}
			}
	;

simple_declare : array_type VAR_NAME
			{
				DBG_YY("simple_declare 1");
				DBG_YY("$1 = "<<to_str($1));
				DBG_YY("$2 = "<<to_str($2));
				YY_ASSERT($1 && $2);
				if($2->ref_count_ > 0){
					if($2->host_cmd_ == CUR_CMD){
						GAMMAR_ERR($1->lineno_,"redefine of '"<<$2->varname_
							<<"', see LINE:"<<$2->lineno_);
						Delete($1);
						YYERROR;
					}else
						$2 = program().NewVar($2->varname_,$2);
				}
				$$ = New<CDeclare>($1->lineno_);
				$$->type_ = 1;
				$$->var_ = $2;
				$$->var_->type_ = 2;
				$$->var_->array_type_ = $1;
				DBG_YY("$$ = "<<to_str($$));
			}
	| sim_type_name	{
				DBG_YY("simple_declare 2");
				DBG_YY("$1 = "<<to_str($1));
				YY_ASSERT($1);
				$$ = New<CDeclare>($1->lineno_);
				$$->type_ = 2;
				$$->var_ = $1;
				DBG_YY("$$ = "<<to_str($$));
			}
	| sim_type_name '=' expr
			{
				DBG_YY("simple_declare 3");
				DBG_YY("$1 = "<<to_str($1));
				DBG_YY("$3 = "<<to_str($3));
				YY_ASSERT($1 && $3);
				$$ = New<CDeclare>($1->lineno_);
				$$->type_ = 3;
				$$->var_ = $1;
				$$->expr_ = $3;
				DBG_YY("$$ = "<<to_str($$));
			}
	| sim_type_name '(' arg_list ')'
			{
				DBG_YY("simple_declare 4");
				DBG_YY("$1 = "<<to_str($1));
				DBG_YY("$3 = "<<to_str($3));
				YY_ASSERT($1);
				$$ = New<CDeclare>($1->lineno_);
				$$->type_ = 4;
				$$->var_ = $1;
				$$->expr_ = New<CExpr>($1->lineno_);
				$$->expr_->type_ = 2;
				$$->expr_->func_call_ =  New<CFuncCall>($1->lineno_);
				$$->expr_->func_call_->ft_token_ = $1->simple_type_;
				$$->expr_->func_call_->arg_list_ = $3;
				DBG_YY("$$ = "<<to_str($$));
			}
	| sim_type_name IEQ expr
			{
				DBG_YY("simple_declare 5");
				DBG_YY("$1 = "<<to_str($1));
				DBG_YY("$3 = "<<to_str($3));
				YY_ASSERT($1 && $3);
				$$ = New<CDeclare>($1->lineno_);
				$$->type_ = 5;
				$$->var_ = $1;
				$$->expr_ = $3;
				DBG_YY("$$ = "<<to_str($$));
			}
	| sim_type_name ':' '(' arg_list ')'
			{
				DBG_YY("simple_declare 6");
				DBG_YY("$1 = "<<to_str($1));
				DBG_YY("$4 = "<<to_str($4));
				YY_ASSERT($1);
				$$ = New<CDeclare>($1->lineno_);
				$$->type_ = 6;
				$$->var_ = $1;
				$$->expr_ = New<CExpr>($1->lineno_);
				$$->expr_->type_ = 2;
				$$->expr_->func_call_ =  New<CFuncCall>($1->lineno_);
				$$->expr_->func_call_->ft_token_ = $1->simple_type_;
				$$->expr_->func_call_->arg_list_ = $4;
				DBG_YY("$$ = "<<to_str($$));
			}
	| sim_type_name comp_op expr
			{
				DBG_YY("simple_declare 7");
				DBG_YY("$1 = "<<to_str($1));
				DBG_YY("$2 = "<<$2);
				DBG_YY("$3 = "<<to_str($3));
				YY_ASSERT($1 && $3);
				$$ = New<CDeclare>($1->lineno_);
				$$->type_ = 7;
				$$->var_ = $1;
				$$->op_token = $2;
				$$->expr_ = $3;
				DBG_YY("$$ = "<<to_str($$));
			}
	| sim_type_name stream_op expr
			{
				DBG_YY("simple_declare 8");
				DBG_YY("$1 = "<<to_str($1));
				DBG_YY("$2 = "<<$2);
				DBG_YY("$3 = "<<to_str($3));
				YY_ASSERT($1 && $3);
				$$ = New<CDeclare>($1->lineno_);
				$$->type_ = 8;
				$$->var_ = $1;
				$$->op_token = $2;
				$$->expr_ = $3;
				DBG_YY("$$ = "<<to_str($$));
			}
	| sim_type_name stream_op simple_type
			{
				DBG_YY("simple_declare 9");
				DBG_YY("$1 = "<<to_str($1));
				DBG_YY("$2 = "<<$2);
				DBG_YY("$3 = "<<$3);
				YY_ASSERT($1);
				$$ = New<CDeclare>($1->lineno_);
				$$->type_ = 9;
				$$->var_ = $1;
				$$->op_token = $2;
				$$->simple_type = $3;
				DBG_YY("$$ = "<<to_str($$));
			}
	;

	/* level 4 */
arg_list : /* empty */
			{
				DBG_YY("arg_list 1");
				$$ = 0;
				DBG_YY("$$ = "<<to_str($$));
			}
	| arg_list_not_empty
			{
				DBG_YY("arg_list 2");
				DBG_YY("$1 = "<<to_str($1));
				YY_ASSERT($1);
				$$ = $1;
				DBG_YY("$$ = "<<to_str($$));
			}
	;

arg_list_not_empty : expr
			{
				DBG_YY("arg_list_not_empty 1");
				DBG_YY("$1 = "<<to_str($1));
				YY_ASSERT($1);
				$$ = New<CArgList>(LINE_NO);
				$$->Add($1);
				DBG_YY("$$ = "<<to_str($$));
			}
	| arg_list_not_empty ',' expr
			{
				DBG_YY("arg_list_not_empty 2");
				DBG_YY("$1 = "<<to_str($1));
				DBG_YY("$3 = "<<to_str($3));
				YY_ASSERT($1 && $3);
				$$ = $1;
				$$->Add($3);
				DBG_YY("$$ = "<<to_str($$));
			}
	;

array_type : simple_type '[' ']'
			{
				DBG_YY("array_type 1");
				DBG_YY("$1 = "<<$1);
				$$ = New<CArrayType>(LINE_NO);
				$$->simple_type_ = $1;
				$$->expr_ = 0;
				DBG_YY("$$ = "<<to_str($$));
			}
	| simple_type '[' expr ']'
			{
				DBG_YY("array_type 2");
				DBG_YY("$1 = "<<$1);
				DBG_YY("$3 = "<<to_str($3));
				YY_ASSERT($3);
				$$ = New<CArrayType>(LINE_NO);
				$$->simple_type_ = $1;
				$$->expr_ = $3;
				DBG_YY("$$ = "<<to_str($$));
			}
	;

sim_type_name : simple_type VAR_NAME
			{
				DBG_YY("sim_type_name 1");
				DBG_YY("$1 = "<<$1);
				DBG_YY("$2 = "<<to_str($2));
				YY_ASSERT($2);
				if($2->ref_count_ > 0){
					if($2->host_cmd_ == CUR_CMD){
						GAMMAR_ERR(LINE_NO,"redefine of '"<<$2->varname_
							<<"', see LINE:"<<$2->lineno_);
						YYERROR;
					}else
						$2 = program().NewVar($2->varname_,$2);
				}
				$$ = $2;
				$$->type_ = 1;
				$$->simple_type_ = $1;
				DBG_YY("$$ = "<<to_str($$));
			}
	;

expr : fix_value	{
				DBG_YY("expr 1");
				DBG_YY("$1 = "<<to_str($1));
				YY_ASSERT($1);
				$$ = New<CExpr>($1->lineno_);
				$$->type_ = 1;
				$$->fix_value_ = $1;
				DBG_YY("$$ = "<<to_str($$));
			}
	| func_call	{
				DBG_YY("expr 2");
				DBG_YY("$1 = "<<to_str($1));
				YY_ASSERT($1);
				$$ = New<CExpr>($1->lineno_);
				$$->type_ = 2;
				$$->func_call_ = $1;
				DBG_YY("$$ = "<<to_str($$));
			}
	| VAR_NAME	{
				DBG_YY("expr 3");
				DBG_YY("$1 = "<<to_str($1));
				YY_ASSERT($1);
				if($1->ref_count_ == 0){
					GAMMAR_ERR(LINE_NO,"undefined variable '"
						<<$1->varname_<<"'");
					YYERROR;	
				}
				$$ = New<CExpr>(LINE_NO);
				$$->type_ = 3;
				$$->var_ = $1;
				DBG_YY("$$ = "<<to_str($$));
			}
	;

	/* basic symbols */
fix_value : NUMBER	{
				DBG_YY("fix_value 1");
				DBG_YY("$1 = "<<$1);
				$$ = New<CFixValue>(LINE_NO);
				$$->type_ = 1;
				$$->number_ = $1;
				DBG_YY("$$ = "<<to_str($$));
			}
	| QSTRING	{
				DBG_YY("fix_value 2");
				DBG_YY("$1 = "<<$1);
				$$ = New<CFixValue>(LINE_NO);
				$$->type_ = 2;
				$$->strIdx_ = $1;
				DBG_YY("$$ = "<<to_str($$));
			}
	;

func_name : FUN		{DBG_YY("func_name = FUN("<<FUN<<")");$$ = FUN;}
	| BEGIN_ 	{DBG_YY("func_name = BEGIN("<<BEGIN_<<")");$$ = BEGIN_;}
	| END		{DBG_YY("func_name = END("<<END<<")");$$ = END;}
	| HBO 		{DBG_YY("func_name = HBO("<<HBO<<")");$$ = HBO;}
	| NBO		{DBG_YY("func_name = NBO("<<NBO<<")");$$ = NBO;}
	| SEND 		{DBG_YY("func_name = SEND("<<SEND<<")");$$ = SEND;}
	| RECV		{DBG_YY("func_name = RECV("<<RECV<<")");$$ = RECV;}
	| HEX 		{DBG_YY("func_name = HEX("<<HEX<<")");$$ = HEX;}
	| UNHEX		{DBG_YY("func_name = UNHEX("<<UNHEX<<")");$$ = UNHEX;}
	;

simple_type : U8	{DBG_YY("simple_type = U8("<<U8<<")");$$ = U8;}
	| S8		{DBG_YY("simple_type = S8("<<S8<<")");$$ = S8;}
	| U16		{DBG_YY("simple_type = U16("<<U16<<")");$$ =  U16;}
	| S16		{DBG_YY("simple_type = S16("<<S16<<")");$$ = S16;}
	| U32		{DBG_YY("simple_type = U32("<<U32<<")");$$ = U32;}
	| S32		{DBG_YY("simple_type = S32("<<S32<<")");$$ = S32;}
	| U64		{DBG_YY("simple_type = U64("<<U64<<")");$$ = U64;}
	| S64		{DBG_YY("simple_type = S64("<<S64<<")");$$ = S64;}
	| STR		{DBG_YY("simple_type = STR("<<STR<<")");$$ = STR;}
	| RAW		{DBG_YY("simple_type = RAW("<<RAW<<")");$$ =  RAW;}
	| TCP		{DBG_YY("simple_type = TCP("<<TCP<<")");$$ = TCP;}
	| UDP		{DBG_YY("simple_type = UDP("<<UDP<<")");$$ = UDP;}
	;

comp_op : OP_LG		{DBG_YY("comp_op = OP_LG("<<OP_LG<<")");$$ = OP_LG;}
	| OP_SM		{DBG_YY("comp_op = OP_SM("<<OP_SM<<")");$$ = OP_SM;}
	| OP_LEQ 	{DBG_YY("comp_op = OP_LEQ("<<OP_LEQ<<")");$$ = OP_LEQ;}
	| OP_SEQ 	{DBG_YY("comp_op = OP_SEQ("<<OP_SEQ<<")");$$ = OP_SEQ;}
	| OP_EQ 	{DBG_YY("comp_op = OP_EQ("<<OP_EQ<<")");$$ = OP_EQ;}
	| OP_NEQ 	{DBG_YY("comp_op = OP_NEQ("<<OP_NEQ<<")");$$ = OP_NEQ;}
	| OP_NOT	{DBG_YY("comp_op = OP_NOT("<<OP_NOT<<")");$$ = OP_NOT;}
	;

stream_op : OP_IN	{DBG_YY("stream_op = OP_IN("<<OP_IN<<")");$$ = OP_IN;}
	| OP_OUT	{DBG_YY("stream_op = OP_OUT("<<OP_OUT<<")");$$ = OP_OUT;}
	;

stmt_sep : ';'		{DBG_YY("stmt_sep = ;");}
	| NL		{DBG_YY("stmt_sep = NL");}
	;