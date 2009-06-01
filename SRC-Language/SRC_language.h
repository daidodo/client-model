#ifndef DOZERG_SRC_LANGUAGE_H_20081126
#define DOZERG_SRC_LANGUAGE_H_20081126

//src : Input buffer(输入缓冲)
//src_len : Length of src(输入缓冲的长度)
//dst : Output buffer(输出缓冲)
//src_len : Init and return length of dst(输出缓冲的初始长度参数，和结果长度的返回值)
typedef bool (*__SRC_UserFunc)(const char * src,unsigned int src_len,char * dst,unsigned int & dst_len);

//版本信息
//version info
#define SRC_version "2.1.153"

//初始化环境
//init environment
void SRC_init();

//编译源文件
//compile source file
bool SRC_compile(const char * filename);

//解释执行
//interpret and run
bool SRC_run(int argc,const char * const * argv);

//注册自定义函数
//register user-defined function
bool SRC_register_function(const char * func_name
    , __SRC_UserFunc func_ptr
    , unsigned int dst_len_max = 65536);

#endif
