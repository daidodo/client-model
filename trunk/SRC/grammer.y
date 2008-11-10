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

%token ARG_NAME

%token NUMBER STRING QSTRING

%token NL IEQ

%token CMD DEF

%%

program : /* empty */	{DBG_YY("program 1");}
	| program program_item	{DBG_YY("program 2");}
	;

program_item:stmt	{DBG_YY("program_item 1");}
	| cmd_define	{DBG_YY("program_item 2");}
	;

stmt :  NL	{DBG_YY("stmt 1");}
	| func_call_list NL	{DBG_YY("stmt 2");}
	| declare NL	{DBG_YY("stmt 3");}
	;

func_call_list : func_call	{DBG_YY("func_call_list 1");}
	| func_call_list func_call	{DBG_YY("func_call_list 2");}
	;

declare : simple_declare	{DBG_YY("declare 1");}
	| def_declare	{DBG_YY("declare 2");}
	;

simple_declare : type ARG_NAME	{DBG_YY("simple_declare 1");}
	| type ARG_NAME '=' expr	{DBG_YY("simple_declare 2");}
	| type ARG_NAME '(' arg_list ')'	{DBG_YY("simple_declare 3");}
	| type ARG_NAME IEQ expr	{DBG_YY("simple_declare 4");}
	| type ARG_NAME ':' '(' arg_list ')'	{DBG_YY("simple_declare 5");}
	;

def_declare : DEF simple_declare	{DBG_YY("def_declare 1");}
	;

expr : fix_value	{DBG_YY("expr 1");}
	| func_call	{DBG_YY("expr 2");}
	| ARG_NAME	{DBG_YY("expr 3");}
	;

func_call : func	{DBG_YY("func_call 1");}
	| func '(' arg_list ')'	{DBG_YY("func_call 2");}
	| type '(' arg_list ')'	{DBG_YY("func_call 3");}
	;

func : BEGIN_ | END	{DBG_YY("func 1");}
	| HBO | NBO	{DBG_YY("func 2");}
	| SEND | RECV	{DBG_YY("func 3");}
	| HEX | UNHEX	{DBG_YY("func 4");}
	;

type : U8 | S8	{DBG_YY("type 1");}
	| U16 | S16	{DBG_YY("type 2");}
	| U32 | S32	{DBG_YY("type 3");}
	| U64 | S64	{DBG_YY("type 4");}
	| STR | RAW	{DBG_YY("type 5");}
	| TCP | UDP	{DBG_YY("type 6");}
	;

arg_list : /* empty */	{DBG_YY("arg_list 1");}
	| arg_list_not_empty	{DBG_YY("arg_list 2");}
	;

arg_list_not_empty : expr	{DBG_YY("arg_list_not_empty 1");}
	| arg_list_not_empty ',' expr	{DBG_YY("arg_list_not_empty 2");}
	;

fix_value : NUMBER	{DBG_YY("fix_value 1");}
	| QSTRING	{DBG_YY("fix_value 2");}
	;

cmd_define : cmd_begin stmt_list cmd_end NL	{DBG_YY("cmd_define 1");}
	;

cmd_begin : CMD	{DBG_YY("cmd_begin 1");}
	| CMD ARG_NAME	{DBG_YY("cmd_begin 2");}
	;

stmt_list : stmt	{DBG_YY("stmt_list 1");}
	| stmt_list stmt	{DBG_YY("stmt_list 2");}
	;

cmd_end : END CMD	{DBG_YY("cmd_end 1");}
	;

