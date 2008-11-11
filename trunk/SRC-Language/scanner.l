%{
#include "common.h"
#include "y.tab.h"

const char * pname;
int lineno = 1;
std::string cur_tok;
%}

nl	\r?\n
ws	[ \t]+
nzero	[1-9][0-9]+
qs	(((\\\")|([^"\n]))*)

%%

"//".* |
#.*	/* comments */;
[ \t]+	;

U8	{cur_tok = yytext;DBG_LEX("U8");return U8;}
S8	{cur_tok = yytext;DBG_LEX("S8");return S8;}
U16	{cur_tok = yytext;DBG_LEX("U16");return U16;}
S16	{cur_tok = yytext;DBG_LEX("S16");return S16;}
U32	{cur_tok = yytext;DBG_LEX("U32");return U32;}
S32	{cur_tok = yytext;DBG_LEX("S32");return S32;}
U64	{cur_tok = yytext;DBG_LEX("U64");return U64;}
S64	{cur_tok = yytext;DBG_LEX("S64");return S64;}
STR	{cur_tok = yytext;DBG_LEX("STR");return STR;}
RAW	{cur_tok = yytext;DBG_LEX("RAW");return RAW;}
TCP	{cur_tok = yytext;DBG_LEX("TCP");return TCP;}
UDP	{cur_tok = yytext;DBG_LEX("UDP");return UDP;}

FUNCTION |
FUN	{cur_tok = yytext;DBG_LEX1("FUN",cur_tok);return FUN;}
BEGIN	{cur_tok = yytext;DBG_LEX("BEGIN");return BEGIN_;}
END	{cur_tok = yytext;DBG_LEX("END");return END;}
HOST_BYTE_ORDER |
HBO	{cur_tok = yytext;DBG_LEX1("HBO",cur_tok);return HBO;}
NET_BYTE_ORDER |
NBO	{cur_tok = yytext;DBG_LEX1("NBO",cur_tok);return NBO;}
SEND	{cur_tok = yytext;DBG_LEX("SEND");return SEND;}
RECV	{cur_tok = yytext;DBG_LEX("RECV");return RECV;}
HEX	{cur_tok = yytext;DBG_LEX("HEX");return HEX;}
UNHEX	{cur_tok = yytext;DBG_LEX("UNHEX");return UNHEX;}

COMMAND |
CMD	{cur_tok = yytext;DBG_LEX1("CMD",cur_tok);return CMD;}

DEFINE |
DEF	{cur_tok = yytext;DBG_LEX1("DEF",cur_tok);return DEF;}

{nl}	{cur_tok = "\\n";DBG_LEX1("NL",cur_tok);++lineno;return NL;}
:=	{cur_tok = yytext;DBG_LEX1("IEQ",cur_tok);return IEQ;}

"<<"	{cur_tok = yytext;DBG_LEX1("OP_OUT",cur_tok);return OP_OUT;}
">>"	{cur_tok = yytext;DBG_LEX1("OP_IN",cur_tok);return OP_IN;}

==	{cur_tok = yytext;DBG_LEX1("OP_EQ",cur_tok);return OP_EQ;}
!=	{cur_tok = yytext;DBG_LEX1("OP_NEQ",cur_tok);return OP_NEQ;}
"<="	{cur_tok = yytext;DBG_LEX1("OP_SEQ",cur_tok);return OP_SEQ;}
">="	{cur_tok = yytext;DBG_LEX1("OP_LEQ",cur_tok);return OP_LEQ;}
"<"	{cur_tok = yytext;DBG_LEX1("OP_SM",cur_tok);return OP_SM;}
">"	{cur_tok = yytext;DBG_LEX1("OP_LG",cur_tok);return OP_LG;}
!	{cur_tok = yytext;DBG_LEX1("NOT",cur_tok);return OP_NOT;}

[_a-zA-Z][_a-zA-Z0-9]*	{cur_tok = yytext;DBG_LEX1("ARG_NAME",cur_tok);return ARG_NAME;}

0|{nzero}[kKmMgG]?	{cur_tok = yytext;DBG_LEX1("NUMBER",cur_tok);return NUMBER;}
\"{qs}\"	{cur_tok = yytext;DBG_LEX1("QSTRING",cur_tok);return QSTRING;}
\"{qs}((\\{nl}){qs}?)+\"	{
		cur_tok = yytext;
		for(size_t i = 0;i < yyleng;++i)  //fix lineno
			if(yytext[i] == '\n')
				++lineno;
		DBG_LEX("QSTRING(NL)");return QSTRING;
	}

	/* error handle */
0[0-9]+	{cur_tok = yytext;ERROR("error number format");}
\"{qs}{nl}	{cur_tok = yytext;ERROR("unterminated string");++lineno;}

.	{cur_tok = yytext;DBG_LEX(*yytext);return *yytext;}

%%

void yyerror(const char * msg){
	std::cerr<<pname<<":"<<lineno<<" : '"<<cur_tok<<"' "
		<<msg<<std::endl;
	exit(1);
}

int yywrap(){
	return 1;
}

int main(int argc,const char ** argv){
	if(argc < 2){
		std::cerr<<"Usage: a.out file\n";
		exit(1);
	}
	FILE * fp = fopen(argv[1],"r");
	if(!fp){
		std::cerr<<"cannot open file '"<<argv[1]<<"'\n";
		exit(1);
	}
	pname = argv[1];
	yyin = fp;
	if(yyparse()){
		std::cerr<<"parse failed\n";
		return 1;
	}
	return 0;
}
