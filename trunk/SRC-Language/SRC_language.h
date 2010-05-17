#ifndef DOZERG_SRC_LANGUAGE_H_20081126
#define DOZERG_SRC_LANGUAGE_H_20081126

#ifdef _USRDLL
#   ifdef SRCDLL_EXPORTS
#       define SRCDLL_API __declspec(dllexport)
#   else
#       define SRCDLL_API __declspec(dllimport)
#   endif
#else
#   define SRCDLL_API
#endif

//prototype of user-defined functions(�û��Զ��庯��ԭ��)
//src : Input buffer(���뻺��)
//src_len : Length of src(���뻺��ĳ���)
//dst : Output buffer(�������)
//src_len : Init and return length of dst(�������ĳ�ʼ���Ȳ������ͽ�����ȵķ���ֵ)
typedef bool (*__SRC_UserFunc)(const char * src,unsigned int src_len,char * dst,unsigned int & dst_len);

//version info(�汾��Ϣ)
#define SRC_version "2.3.217"

//init environment(��ʼ������)
SRCDLL_API void SRC_init();

//compile source file(����Դ�ļ�)
SRCDLL_API bool SRC_compile(const char * filename);

//interpret and run(����ִ��)
SRCDLL_API bool SRC_run(int argc = 0,const char * const * argv = 0);

//register user-defined function(ע���û��Զ��庯��)
SRCDLL_API bool SRC_register_function(const char * func_name
    , __SRC_UserFunc func_ptr
    , unsigned int dst_len_max = 65536);

#endif
