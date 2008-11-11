#include <iostream>
#include <string>

//using namespace std;

extern int lineno;

#define ERROR(msg) yyerror(msg)

void yyerror(const char * msg);

int yylex();

int yyparse();

#define DBG_LEX(msg)    {std::cout<<"lex "<<lineno<<" : "<<msg<<std::endl;}
#define DBG_LEX1(t,v)   {std::cout<<"lex "<<lineno<<" : "<<t<<"("<<v<<")\n";} 
#define DBG_YY(msg)     {std::cout<<"yy "<<lineno<<" : "<<msg<<std::endl;}
