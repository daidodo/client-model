%{
#include <string>
#include <vector>
#include <map>
#include "common.h"

std::vector<std::string> qstr_table;
std::map<std::string,CExpr> arg_table;
%}

%token NL IEQ
%token CMD DEF
%token U8 S8 U16 S16 U32 S32 U64 S64 STR RAW TCP UDP
%token FUN BEGIN_ END HBO NBO SEND RECV HEX UNHEX
%token OP_LG OP_SM OP_LEQ OP_SEQ OP_EQ OP_NEQ OP_NOT OP_IN OP_OUT
%token <number_> NUMBER
%token <strIdx_> QSTRING
%token <argname_> ARG_NAME

%type <token_> simple_type func_name comp_op stream_op
%type <fix_value_> fix_value
%type <expr_> expr
%type <sim_type_name_> sim_type_name
%type <array_type_> array_type
%type <arg_list_> arg_list arg_list_not_empty
%type <assert_exp_> assert_exp
%type <simple_declare_> simple_declare def_declare
%type <func_call_> func_call

%union{
	int		token_;
	int		number_;
	size_t		strIdx_;
	__Argname	argname_;
	CFixValue *	fix_value_;
	CExpr *		expr_;
	CSimTypeName *	sim_type_name_;
	CArrayType *	array_type_;
	__ArgList *	arg_list_;
	CAssertExp *	assert_exp_;
	CSimDeclare *	simple_declare_;
	CFuncCall *	func_call_;
}
%%
	/* top */
program : /* empty */	{DBG_YY("program 1");}
	| program program_item	{DBG_YY("program 2");}
	;

program_item : stmt	{DBG_YY("program_item 1");}
	| cmd_define	{DBG_YY("program_item 2");}
	;

	/* level 1 */
stmt :  stmt_sep	{DBG_YY("stmt 1");}
	| func_call_list stmt_sep	{DBG_YY("stmt 2");}
	| declare stmt_sep	{DBG_YY("stmt 3");}
	;

cmd_define : cmd_begin stmt_assert_list cmd_end stmt_sep	{DBG_YY("cmd_define 1");}
	;

	/* level 2 */
func_call_list : func_call	{DBG_YY("func_call_list 1");}
	| func_call_list func_call	{DBG_YY("func_call_list 2");}
	;

declare : simple_declare	{DBG_YY("declare 1");}
	| def_declare	{DBG_YY("declare 2");}
	;

stmt_assert_list : stmt	{DBG_YY("stmt_list 1");}
	| stmt_assert_list stmt	{DBG_YY("stmt_list 2");}
	| stmt_assert_list assert_exp	{DBG_YY("stmt_list 3");}
	;

	/* level 3 */
func_call : func_name	{DBG_YY("func_call 1");}
	| func_name '(' arg_list ')'	{DBG_YY("func_call 2");}
	| simple_type '(' arg_list ')'	{DBG_YY("func_call 3");}
	;

def_declare : DEF simple_declare	{DBG_YY("def_declare 1");}
	;

simple_declare : array_type ARG_NAME		{DBG_YY("simple_declare 1");}
	| sim_type_name				{DBG_YY("simple_declare 2");}
	| sim_type_name '=' expr		{DBG_YY("simple_declare 3");}
	| sim_type_name '(' arg_list ')'	{DBG_YY("simple_declare 4");}
	| sim_type_name IEQ expr		{DBG_YY("simple_declare 5");}
	| sim_type_name ':' '(' arg_list ')'	{DBG_YY("simple_declare 6");}
	| sim_type_name comp_op expr		{DBG_YY("simple_declare 7");}
	| sim_type_name stream_op expr		{DBG_YY("simple_declare 8");}
	| sim_type_name stream_op simple_type	{DBG_YY("simple_declare 9");}
	;

assert_exp : expr comp_op expr		{DBG_YY("assert_exp 1");}
	| comp_op expr			{DBG_YY("assert_exp 2");}
	;

	/* level 4 */
arg_list : /* empty */			{DBG_YY("arg_list 1");}
	| arg_list_not_empty		{DBG_YY("arg_list 2");}
	;

arg_list_not_empty : expr		{DBG_YY("arg_list_not_empty 1");}
	| arg_list_not_empty ',' expr	{DBG_YY("arg_list_not_empty 2");}
	;

array_type : simple_type '[' ']'	{DBG_YY("array_type 1");}
	| simple_type '[' expr ']'	{DBG_YY("array_type 2");}
	;

sim_type_name : simple_type ARG_NAME	{DBG_YY("sim_type_name 1");}
	;

expr : fix_value	{DBG_YY("expr 1");}
	| func_call	{DBG_YY("expr 2");}
	| ARG_NAME	{DBG_YY("expr 3");}
	;

	/* basic symbols */
cmd_begin : CMD		{DBG_YY("cmd_begin 1");}
	| CMD ARG_NAME	{DBG_YY("cmd_begin 2");}
	;

cmd_end : END CMD	{DBG_YY("cmd_end 1");}
	;

stmt_sep : ';'		{DBG_YY("stmt_sep 1");}
	| NL		{DBG_YY("stmt_sep 2");}
	;

func_name : FUN		{DBG_YY("func_name 1");}
	| BEGIN_ 	{DBG_YY("func_name 2");}
	| END		{DBG_YY("func_name 3");}
	| HBO 		{DBG_YY("func_name 4");}
	| NBO		{DBG_YY("func_name 5");}
	| SEND 		{DBG_YY("func_name 6");}
	| RECV		{DBG_YY("func_name 7");}
	| HEX 		{DBG_YY("func_name 8");}
	| UNHEX		{DBG_YY("func_name 9");}
	;

simple_type : U8	{DBG_YY("simple_type 1");}
	| S8		{DBG_YY("simple_type 2");}
	| U16		{DBG_YY("simple_type 3");}
	| S16		{DBG_YY("simple_type 4");}
	| U32		{DBG_YY("simple_type 5");}
	| S32		{DBG_YY("simple_type 6");}
	| U64		{DBG_YY("simple_type 7");}
	| S64		{DBG_YY("simple_type 8");}
	| STR		{DBG_YY("simple_type 9");}
	| RAW		{DBG_YY("simple_type 10");}
	| TCP		{DBG_YY("simple_type 11");}
	| UDP		{DBG_YY("simple_type 12");}
	;

comp_op : OP_LG		{DBG_YY("comp_op 1");}
	| OP_SM		{DBG_YY("comp_op 2");}
	| OP_LEQ 	{DBG_YY("comp_op 3");}
	| OP_SEQ 	{DBG_YY("comp_op 4");}
	| OP_EQ 	{DBG_YY("comp_op 5");}
	| OP_NEQ 	{DBG_YY("comp_op 6");}
	| OP_NOT	{DBG_YY("comp_op 7");}
	;

stream_op : OP_IN	{DBG_YY("stream_op 1");}
	| OP_OUT	{DBG_YY("stream_op 2");}
	;

fix_value : NUMBER	{DBG_YY("fix_value 1");}
	| QSTRING	{DBG_YY("fix_value 2");}
	;

