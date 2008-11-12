#include <iostream>
#include "symbols.h"

#define ERROR(msg) yyerror(msg)

extern FILE * yyin;

void yyerror(const char * msg);

int yylex();

int yyparse();

#define DBG_LEX(msg)    //{std::cout<<"lex "<<global().lineno<<" : "<<msg<<std::endl;}
#define DBG_LEX1(t,v)   //{std::cout<<"lex "<<global().lineno<<" : "<<t<<"("<<v<<")\n";} 
#define DBG_YY(msg)     {std::cout<<"yy "<<global().lineno<<" : "<<msg<<std::endl;}
