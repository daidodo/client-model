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

%token IEQ

%token CMD

%%

program : stmt_list cmd_list	{DBG_YY("program");}
	;

stmt_list: 	{DBG_YY("stmt_list 1");}
	| stmt_list stmt	{DBG_YY("stmt_list 2");}
	;

stmt :  func_call	{DBG_YY("stmt 1");}
	| declare	{DBG_YY("stmt 2");}
	;

declare : type ARG_NAME	{DBG_YY("declare 1");}
	| type ARG_NAME '=' expr	{DBG_YY("declare 2");}
	| type ARG_NAME IEQ expr	{DBG_YY("declare 3");}
	| type ARG_NAME '(' arg_list ')'	{DBG_YY("declare 4");}
	;

expr : fix_value	{DBG_YY("expr 1");}
	| func_call	{DBG_YY("expr 2");}
	| ARG_NAME	{DBG_YY("expr 3");}
	;

func_call : func	{DBG_YY("func_call 1");}
	| func '(' ')'	{DBG_YY("func_call 2");}
	| func '(' arg_list ')'	{DBG_YY("func_call 3");}
	| type '(' ')'	{DBG_YY("func_call 4");}
	| type '(' arg_list ')'	{DBG_YY("func_call 5");}
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

arg_list : expr	{DBG_YY("arg_list 1");}
	| arg_list ',' expr	{DBG_YY("arg_list 2");}
	;

fix_value : NUMBER	{DBG_YY("fix_value 1");}
	| QSTRING	{DBG_YY("fix_value 2");}
	;

cmd_list : cmd_define	{DBG_YY("cmd_list 1");}
	| cmd_list cmd_define	{DBG_YY("cmd_list 2");}
	;

cmd_define : cmd_begin stmt_list cmd_end	{DBG_YY("cmd_define");}
	;

cmd_begin : CMD ARG_NAME	{DBG_YY("cmd_begin");}
	;

cmd_end : END CMD	{DBG_YY("cmd_end");}
	;
%%

