#ifndef DOZERG_COMMON_H_20081111
#define DOZERG_COMMON_H_20081111

#define DBG_LEX(msg)    //{std::cout<<"lex "<<global().lineno<<" : "<<msg<<std::endl;}
#define DBG_LEX1(t,v)   //{std::cout<<"lex "<<global().lineno<<" : "<<t<<"("<<v<<")\n";} 
#define DBG_YY(msg)     {std::cout<<"yy "<<global().lineno<<" : "<<msg<<std::endl;}

#endif
