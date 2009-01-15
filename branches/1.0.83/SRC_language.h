#ifndef DOZERG_SRC_LANGUAGE_H_20081126
#define DOZERG_SRC_LANGUAGE_H_20081126

#include <vector>
#include <string>

#ifdef WIN32
#   ifdef EXPORT_DLL
#       define EXPORT_API __declspec(dllexport)
#   else
#       define EXPORT_API __declspec(dllimport)
#   endif
#else
#   define EXPORT_API
#endif

//版本信息
//version info
#define SRC_version "1.1.99"

//初始化环境
//init environment
EXPORT_API void SRC_init();

//编译源文件
//compile source file
EXPORT_API bool SRC_compile(const std::string & filename);

//解释执行
//interpret and run
EXPORT_API bool SRC_run();

//注册自定义函数
//register user-defined function
EXPORT_API bool SRC_register_function(const std::string & func_name,
    bool (*func_ptr)(std::vector<char> & src,std::vector<char> & dst));

#endif
