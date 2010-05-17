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

//prototype of user-defined functions(用户自定义函数原型)
//src : Input buffer(输入缓冲)
//src_len : Length of src(输入缓冲的长度)
//dst : Output buffer(输出缓冲)
//src_len : Init and return length of dst(输出缓冲的初始长度参数，和结果长度的返回值)
typedef bool (*__SRC_UserFunc)(const char * src,unsigned int src_len,char * dst,unsigned int & dst_len);

//version info(版本信息)
#define SRC_version "2.3.217"

//init environment(初始化环境)
SRCDLL_API void SRC_init();

//compile source file(编译源文件)
SRCDLL_API bool SRC_compile(const char * filename);

//interpret and run(解释执行)
SRCDLL_API bool SRC_run(int argc = 0,const char * const * argv = 0);

//register user-defined function(注册用户自定义函数)
SRCDLL_API bool SRC_register_function(const char * func_name
    , __SRC_UserFunc func_ptr
    , unsigned int dst_len_max = 65536);

#endif
