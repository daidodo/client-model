%{
#include <iostream>
#include "global.h"
#include "util.h"
#include "errors.h"
#include "dbg.h"
#include "y.tab.h"
%}

%x QSTR_S
%s EOF_S

nl	(\r?\n)
nzero	([1-9][0-9]*)

%%

<QSTR_S>\\a	{CUR_TOK.push_back('\a');}
<QSTR_S>\\b	{CUR_TOK.push_back('\b');}
<QSTR_S>\\f	{CUR_TOK.push_back('\f');}
<QSTR_S>\\n	{CUR_TOK.push_back('\n');}
<QSTR_S>\\r	{CUR_TOK.push_back('\r');}
<QSTR_S>\\t	{CUR_TOK.push_back('\t');}
<QSTR_S>\\v	{CUR_TOK.push_back('\v');}
<QSTR_S>\\\"	{CUR_TOK.push_back('\"');}
<QSTR_S>\\[0-7]{1,3}	{
				int ch = atoi_base8(yytext + 1,yyleng - 1);
				if(ch > 255){
					CUR_TOK = yytext;
					SYNTAX_ERR("char value overflow");
				}
				CUR_TOK.push_back(ch);
			}
<QSTR_S>\\x[a-fA-F0-9]{1,2}	{
					int ch = atoi_base16(yytext + 1,yyleng - 1);
					if(ch > 255){
						CUR_TOK = yytext;
						SYNTAX_ERR("char value overflow");
					}
					CUR_TOK.push_back(ch);
				}

<QSTR_S>\\{nl}	{++LINE_NO;}
<QSTR_S>\\.	{CUR_TOK.push_back(yytext[1]);}
<QSTR_S>{nl}	{SYNTAX_ERR("unterminated string");}
<QSTR_S>\"	{
			BEGIN INITIAL;
			yylval.strIdx_ = program().AddQstr(CUR_TOK);
			return QSTRING;
		}
<QSTR_S>.	{CUR_TOK.push_back(*yytext);}

"//".* |
#.*	/* comments */;
[ \t]+	;

\"	{CUR_TOK.clear();BEGIN QSTR_S;}

U8	{CUR_TOK = yytext;DBG_LEX("U8");return U8;}
S8	{CUR_TOK = yytext;DBG_LEX("S8");return S8;}
U16	{CUR_TOK = yytext;DBG_LEX("U16");return U16;}
S16	{CUR_TOK = yytext;DBG_LEX("S16");return S16;}
U32	{CUR_TOK = yytext;DBG_LEX("U32");return U32;}
S32	{CUR_TOK = yytext;DBG_LEX("S32");return S32;}
U64	{CUR_TOK = yytext;DBG_LEX("U64");return U64;}
S64	{CUR_TOK = yytext;DBG_LEX("S64");return S64;}
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

0|{nzero}[kKmMgG]?	{
				CUR_TOK = yytext;
				DBG_LEX1("NUMBER",CUR_TOK);
				yylval.number_ = str2int(yytext,yyleng);
				return NUMBER;
			}

	/* error handle */
0[0-9]+	{CUR_TOK = yytext;SYNTAX_ERR("error number format");}

<EOF_S><<EOF>>	{return 0;}
<<EOF>>	{CUR_TOK = "EOF";DBG_LEX(CUR_TOK);BEGIN EOF_S;return EOF_;}
.	{CUR_TOK = yytext;DBG_LEX(*yytext);return *yytext;}

%%

int yywrap(){
	return 1;
}
