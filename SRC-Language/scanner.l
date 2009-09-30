%{
#if defined(WIN32) && !defined(YY_NO_UNISTD_H)
#   define YY_NO_UNISTD_H
#endif
#include "global.h"
#include "dbg.h"
#include "y.tab.h"
#include "yystype.h"
%}

%x CHAR_S QSTR_S RSTR_S
%s EOF_S

nl		(\r?\n)
digit		([0-9])
nz_digit	([1-9])
oct_digit	([0-7])
hex_digit	([0-9a-fA-F])
int_suf		([uU])
long_suf	(({int_suf}[lL])|([lL]{int_suf}?))
i64_suf		(i64|ll|LL)

hex_const	((0x|0X){hex_digit}+)
oct_const	(0{oct_digit}+)
dec_const	(0|({nz_digit}{digit}*))
int_const_val	([+-]?({hex_const}|{oct_const}|{dec_const}))
int_const	({int_const_val}{int_suf}?)
long_const	({int_const_val}{long_suf}?)
i64_const	({int_const_val}{i64_suf}?)

%%

<EOF_S><<EOF>>	|
<EOF_S>.|\n	{return 0;}

<QSTR_S,CHAR_S>\\a	{CUR_TOK.push_back('\a');}
<QSTR_S,CHAR_S>\\b	{CUR_TOK.push_back('\b');}
<QSTR_S,CHAR_S>\\f	{CUR_TOK.push_back('\f');}
<QSTR_S,CHAR_S>\\n	{CUR_TOK.push_back('\n');}
<QSTR_S,CHAR_S>\\r	{CUR_TOK.push_back('\r');}
<QSTR_S,CHAR_S>\\t	{CUR_TOK.push_back('\t');}
<QSTR_S,CHAR_S>\\v	{CUR_TOK.push_back('\v');}
<QSTR_S,CHAR_S>\\\"	{CUR_TOK.push_back('\"');}
<RSTR_S>\\\"		{CUR_TOK += yytext;}
<QSTR_S,CHAR_S>\\'	{CUR_TOK.push_back('\'');}
<QSTR_S,CHAR_S>\\[0-7]{1,3}	{
				int ch = str2num_base8<int>(yytext + 1,yyleng - 1);
				if(ch > 255){
					CUR_TOK = yytext;
					SYNTAX_ERR("char value overflow");
				}
				CUR_TOK.push_back(ch);
			}
<QSTR_S,CHAR_S>\\x[a-fA-F0-9]{1,2}	{
					int ch = str2num_base16<int>(yytext + 2,yyleng - 2);
					if(ch > 255){
						CUR_TOK = yytext;
						SYNTAX_ERR("char value overflow");
					}
					CUR_TOK.push_back(ch);
				}

<QSTR_S,CHAR_S>\\{nl}	{++LINE_NO;}
<RSTR_S>\\{nl}		{
				++LINE_NO;
				CUR_TOK += yytext;
			}
<QSTR_S,CHAR_S>\\.	{CUR_TOK.push_back(yytext[1]);}
<QSTR_S,RSTR_S>\"	{
				BEGIN INITIAL;
				DBG_LEX1("QSTRING",CUR_TOK);
				yylval.strIdx_ = program().AddQstr(CUR_TOK);
				return QSTRING;
			}
<CHAR_S>'		{
				BEGIN INITIAL;
				if(CUR_TOK.size() != 1){
					SYNTAX_ERR("invalid charactor");
				}
				yylval.int_ = CUR_TOK[0];
				DBG_LEX1("CHAR",yylval.int_);
				return INT;
			}
<QSTR_S,CHAR_S,RSTR_S>.	{CUR_TOK.push_back(*yytext);}
<QSTR_S,CHAR_S,RSTR_S>{nl}	{SYNTAX_ERR("unterminated string");BEGIN INITIAL;}

"//".* |
#.*	/* comments */;
[ \t]+	;

[rR]\"	{CUR_TOK.clear();BEGIN RSTR_S;}
\"	{CUR_TOK.clear();BEGIN QSTR_S;}
'	{CUR_TOK.clear();BEGIN CHAR_S;}

U8	{CUR_TOK = yytext;DBG_LEX("U8");return TP_U8;}
S8	{CUR_TOK = yytext;DBG_LEX("S8");return TP_S8;}
U16	{CUR_TOK = yytext;DBG_LEX("U16");return TP_U16;}
S16	{CUR_TOK = yytext;DBG_LEX("S16");return TP_S16;}
U32	{CUR_TOK = yytext;DBG_LEX("U32");return TP_U32;}
S32	{CUR_TOK = yytext;DBG_LEX("S32");return TP_S32;}
U64	{CUR_TOK = yytext;DBG_LEX("U64");return TP_U64;}
S64	{CUR_TOK = yytext;DBG_LEX("S64");return TP_S64;}
STR	{CUR_TOK = yytext;DBG_LEX("STR");return STR;}
RAW	{CUR_TOK = yytext;DBG_LEX("RAW");return RAW;}
TCP	{CUR_TOK = yytext;DBG_LEX("TCP");return TCP;}
UDP	{CUR_TOK = yytext;DBG_LEX("UDP");return UDP;}

FUNCTION |
FUN	{CUR_TOK = yytext;DBG_LEX1("FUN",CUR_TOK);return FUN;}
BEGIN	{CUR_TOK = yytext;DBG_LEX("BEGIN");return BEGIN_;}
END	{CUR_TOK = yytext;DBG_LEX("END");return END;}
HOST_BYTE_ORDER |
HBO	{CUR_TOK = yytext;DBG_LEX1("HBO",CUR_TOK);return HBO;}
NET_BYTE_ORDER |
NBO	{CUR_TOK = yytext;DBG_LEX1("NBO",CUR_TOK);return NBO;}
SEND	{CUR_TOK = yytext;DBG_LEX("SEND");return SEND;}
RECV	{CUR_TOK = yytext;DBG_LEX("RECV");return RECV;}
HEX	{CUR_TOK = yytext;DBG_LEX("HEX");return HEX;}
UNHEX	{CUR_TOK = yytext;DBG_LEX("UNHEX");return UNHEX;}
PRINT	{CUR_TOK = yytext;DBG_LEX("PRINT");return PRINT;}
IP	{CUR_TOK = yytext;DBG_LEX("IP");return IP;}
ARRAY	{CUR_TOK = yytext;DBG_LEX("ARRAY");return ARRAY;}
SLEEP	{CUR_TOK = yytext;DBG_LEX("SLEEP");return SLEEP;}
DEBUG	{CUR_TOK = yytext;DBG_LEX("DEBUG");return __DEBUG;}

COMMAND |
CMD	{CUR_TOK = yytext;DBG_LEX1("CMD",CUR_TOK);return CMD;}

DEFINE |
DEF	{CUR_TOK = yytext;DBG_LEX1("DEF",CUR_TOK);return DEF;}

{nl}	{CUR_TOK = "\\n";DBG_LEX1("NL",CUR_TOK);++LINE_NO;return NL;}
:=	{CUR_TOK = yytext;DBG_LEX1("IEQ",CUR_TOK);return IEQ;}

"<<"	{CUR_TOK = yytext;DBG_LEX1("OP_OUT",CUR_TOK);return OP_OUT;}
">>"	{CUR_TOK = yytext;DBG_LEX1("OP_IN",CUR_TOK);return OP_IN;}

==	{CUR_TOK = yytext;DBG_LEX1("OP_EQ",CUR_TOK);return OP_EQ;}
!=	{CUR_TOK = yytext;DBG_LEX1("OP_NEQ",CUR_TOK);return OP_NEQ;}
"<="	{CUR_TOK = yytext;DBG_LEX1("OP_SEQ",CUR_TOK);return OP_SEQ;}
">="	{CUR_TOK = yytext;DBG_LEX1("OP_LEQ",CUR_TOK);return OP_LEQ;}
"<"	{CUR_TOK = yytext;DBG_LEX1("OP_SM",CUR_TOK);return OP_SM;}
">"	{CUR_TOK = yytext;DBG_LEX1("OP_LG",CUR_TOK);return OP_LG;}
!	{CUR_TOK = yytext;DBG_LEX1("NOT",CUR_TOK);return OP_NOT;}

[_a-zA-Z][_a-zA-Z0-9]*	{
				CUR_TOK = yytext;
				DBG_LEX1("VAR_NAME",CUR_TOK);
				yylval.var_ = program().GetVar(CUR_TOK);
				return VAR_NAME;
			}
{int_const}[kKmMgG]?	{
				CUR_TOK = yytext;
				DBG_LEX1("INT",CUR_TOK);
				yylval.int_ = str2int(yytext,yyleng);
				return INT;
			}
{long_const}[kKmMgG]?	{
				CUR_TOK = yytext;
				DBG_LEX1("LONG",CUR_TOK);
				yylval.long_ = str2long(yytext,yyleng);
				return LONG;
			}
{long_const}[tTpPeE]	{
				CUR_TOK = yytext;
				DBG_LEX1("LONG",CUR_TOK);
				if(sizeof(long) < 8){
					SYNTAX_ERR(yytext[yyleng - 1]<<"is invalid for long(4 bytes)");
				}
				yylval.long_ = str2long(yytext,yyleng);
				return LONG;
			}
{i64_const}[kKmMgGtTpPeE]?	{
				CUR_TOK = yytext;
				DBG_LEX1("I64",CUR_TOK);
				yylval.i64_ = str2i64(yytext,yyleng);
				return I64;
			}

\${digit}+		{
				CUR_TOK = yytext;
				DBG_LEX1("PROG_ARG",CUR_TOK);
				yylval.prog_arg_ = atoi(yytext + 1);	//skip '$'
				return PROG_ARG;
			}

<<EOF>>	{CUR_TOK = "EOF";DBG_LEX(CUR_TOK);BEGIN EOF_S;return EOF_;}
.	{CUR_TOK = yytext;DBG_LEX(*yytext);return *yytext;}

%%

int yywrap(){
	return 1;
}
