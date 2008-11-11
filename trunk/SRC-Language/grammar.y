%{
#include "common.h"
%}

%token U8 S8
%token U16 S16
%token U32 S32
%token U64 S64
%token STR RAW
%token TCP UDP

%token BEGIN_ END HBO NBO SEND RECV HEX UNHEX

%token COMP STREAM

%token ARG_NAME

%token NUMBER STRING QSTRING

%token SEMI NL IEQ

%token CMD DEF

%nonassoc COMP
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
	| stmt_assert_list assert	{DBG_YY("stmt_list 3");}
	;

	/* level 3 */
func_call : func_name	{DBG_YY("func_call 1");}
	| func_name '(' arg_list ')'	{DBG_YY("func_call 2");}
	| simple_type '(' arg_list ')'	{DBG_YY("func_call 3");}
	;

simple_declare : array_type ARG_NAME	{DBG_YY("simple_declare 1");}
	| sim_type_name	{DBG_YY("simple_declare 2");}
	| sim_type_name '=' expr	{DBG_YY("simple_declare 3");}
	| sim_type_name '(' arg_list ')'	{DBG_YY("simple_declare 4");}
	| sim_type_name IEQ expr	{DBG_YY("simple_declare 5");}
	| sim_type_name ':' '(' arg_list ')'	{DBG_YY("simple_declare 6");}
	| sim_type_name COMP expr	{DBG_YY("simple_declare 7");}
	| sim_type_name STREAM expr	{DBG_YY("simple_declare 8");}
	| sim_type_name STREAM simple_type	{DBG_YY("simple_declare 9");}
	;

def_declare : DEF simple_declare	{DBG_YY("def_declare 1");}
	;

assert : expr COMP expr	{DBG_YY("assert 1");}
	| COMP expr	{DBG_YY("assert 2");}
	;

	/* level 4 */
arg_list : /* empty */	{DBG_YY("arg_list 1");}
	| arg_list_not_empty	{DBG_YY("arg_list 2");}
	;

arg_list_not_empty : expr	{DBG_YY("arg_list_not_empty 1");}
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
cmd_begin : CMD	{DBG_YY("cmd_begin 1");}
	| CMD ARG_NAME	{DBG_YY("cmd_begin 2");}
	;

cmd_end : END CMD	{DBG_YY("cmd_end 1");}
	;

stmt_sep : SEMI	{DBG_YY("stmt_sep 1");}
	| NL	{DBG_YY("stmt_sep 2");}
	;

func_name : BEGIN_ | END	{DBG_YY("func_name 1");}
	| HBO | NBO	{DBG_YY("func_name 2");}
	| SEND | RECV	{DBG_YY("func_name 3");}
	| HEX | UNHEX	{DBG_YY("func_name 4");}
	;

simple_type : U8 | S8	{DBG_YY("simple_type 1");}
	| U16 | S16	{DBG_YY("simple_type 2");}
	| U32 | S32	{DBG_YY("simple_type 3");}
	| U64 | S64	{DBG_YY("simple_type 4");}
	| STR | RAW	{DBG_YY("simple_type 5");}
	| TCP | UDP	{DBG_YY("simple_type 6");}
	;

fix_value : NUMBER	{DBG_YY("fix_value 1");}
	| QSTRING	{DBG_YY("fix_value 2");}
	;

