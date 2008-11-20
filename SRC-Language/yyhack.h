/*
    ��Ϊyacc���ɵ���C���ԣ���YYSTYPE��C++���ͣ�
    ������Ҫ��realloc��malloc����һЩ���ӹ�����
    ��ʵ����Ҫ��ֻ��һ��memset...
//*/

#ifdef YYBYACC

#include <cstdlib>  //for malloc
#include <cstring>  //for memset

//reallocû��hack,��Ϊ��֪������ԭ���Ĵ�С,
//û����ԭ�������ݸ��Ƶ���������
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

/*    ����İ汾
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

