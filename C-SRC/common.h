#include <iostream>
#include <string>

using namespace std;

extern int lineno;
//extern std::string cur_tok;
	
#define ERROR(msg) yyerror(msg)

void yyerror(const char * msg);

int yylex();

int yyparse();

#define DBG_LEX(msg)	{cout<<"lex "<<lineno<<" : "<<msg<<endl;} 
#define DBG_YY(msg)		{cout<<"yy "<<lineno<<" : "<<msg<<endl;}
