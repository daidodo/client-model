/*
    因为yacc生成的是C语言，而YYSTYPE是C++类型，
    所以需要对realloc和malloc进行一些“加工”，
    其实我需要的只是一个memset...
//*/

#ifdef YYBYACC

#include <cstdlib>  //for malloc
#include <cstring>  //for memset

//realloc没法hack,因为不知道数组原来的大小,
//没法把原来的数据复制到新数组里
void * __realloc_hack(void * p,size_t sz)
{
    return 0;
    //p = realloc(p,sz);
    //if(p)
    //    memset(p,0,sz);
    //return p;
}

void * __malloc_hack(size_t sz)
{
    void * p = malloc(sz);
    if(p)
        memset(p,0,sz);
    return p;
}

/*    最初的版本
template<class T>
T * __realloc_hack(T * p,size_t sz)
{
    delete [] p;
    p = new T[sz / sizeof(T)];
    return p;
}

void * __malloc_hack(size_t sz)
{
    return new YYSTYPE[sz / sizeof(YYSTYPE)];
}
//*/

#define realloc __realloc_hack
#define malloc  __malloc_hack

#endif

