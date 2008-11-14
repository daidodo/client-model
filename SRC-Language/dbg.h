#ifndef DOZERG_COMMON_H_20081111
#define DOZERG_COMMON_H_20081111

#include "config.h"

#if __LEXICAL_DEBUG
#   define DBG_LEX(msg)     {std::cout<<"lex "<<global().lineno<<" : "<<msg<<std::endl;}
#   define DBG_LEX1(t,v)    {std::cout<<"lex "<<global().lineno<<" : "<<t<<"("<<v<<")\n";} 
#else
#   define DBG_LEX(msg)
#   define DBG_LEX1(t,v)
#endif

#if __SYNTAX_DEBUG
#   define DBG_YY(msg)      {std::cout<<"yy "<<global().lineno<<" : "<<msg<<std::endl;}
#else
#   define DBG_YY(msg)
#endif

#if __GRAMMAR_DEBUG
#   define DBG_GMM(msg)      {std::cout<<"gmm "<<global().lineno<<" : "<<msg<<std::endl;}
#else
#   define DBG_GMM(msg)
#endif

#define YY_ASSERT(expr)     {assert(expr);}

#endif
