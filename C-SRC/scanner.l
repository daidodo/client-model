%{
#include "common.h"
#include "y.tab.h"

int lineno = 1;
std::string cur_tok;
%}

qs	(((\\\")|([^"\n]))*)
nzero	[1-9][0-9]+
nl	\r*\n
ws	[ \t]+
%%

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

BEGIN	{cur_tok = yytext;DBG_LEX("BEGIN");return BEGIN_;}
END	{cur_tok = yytext;DBG_LEX("END");return END;}
HBO	{cur_tok = yytext;DBG_LEX("HBO");return HBO;}
NBO	{cur_tok = yytext;DBG_LEX("NBO");return NBO;}
SEND	{cur_tok = yytext;DBG_LEX("SEND");return SEND;}
RECV	{cur_tok = yytext;DBG_LEX("RECV");return RECV;}
HEX	{cur_tok = yytext;DBG_LEX("HEX");return HEX;}
UNHEX	{cur_tok = yytext;DBG_LEX("UNHEX");return UNHEX;}

CMD	{cur_tok = yytext;DBG_LEX("CMD");return CMD;}

{nl}	{cur_tok = "\\n";DBG_LEX("{nl}");++lineno;}
:=	{cur_tok = yytext;DBG_LEX("IEQ");return IEQ;}

[_a-zA-Z][_a-zA-Z0-9]*	{cur_tok = yytext;DBG_LEX("ARG_NAME");return ARG_NAME;}

0|{nzero}	{cur_tok = yytext;DBG_LEX("NUMBER");return NUMBER;}
\"{qs}\"	{cur_tok = yytext;DBG_LEX("QSTRING");return QSTRING;}

	/* error handle */
0[0-9]+	{cur_tok = yytext;ERROR("error number format");}
\"{qs}$	{cur_tok = yytext;ERROR("unterminated string");}

.	{cur_tok = yytext;DBG_LEX(".");return *yytext;}

%%

void yyerror(const char * msg){
	cerr<<lineno<<" : '"<<cur_tok<<"' "<<msg<<endl;
	//for(size_t i = 0;i < cur_tok.length();++i)
	//	cerr<<hex<<"["<<int(cur_tok[i])<<"]";
	//cerr<<dec<<"' "<<msg<<"\n";
	exit(1);
}

int yywrap(){
	return 1;
}

int main(int argc,const char ** argv){
	if(argc < 2){
		cerr<<"Usage: a.out file\n";
		exit(1);
	}
	FILE * fp = fopen(argv[1],"r");
	if(!fp){
		cerr<<"cannot open file '"<<argv[1]<<"'\n";
		exit(1);
	}
	yyin = fp;
	if(yyparse()){
		cerr<<"parse failed\n";
		return 1;
	}
	return 0;
}
