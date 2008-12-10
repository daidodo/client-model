#ifndef DOZERG_SRC_LANGUAGE_H_20081126
#define DOZERG_SRC_LANGUAGE_H_20081126

#include <vector>
#include <string>

//版本信息
//version info
#define SRC_version "1.1.94"

//初始化环境
//init environment
void SRC_init();

//编译源文件
//compile source file
bool SRC_compile(const std::string & filename);

//解释执行
//interpret and run
bool SRC_run();

//注册自定义函数
//register user-defined function
bool SRC_register_function(const std::string & func_name,
    bool (*func_ptr)(std::vector<char> & src,std::vector<char> & dst));

#endif
