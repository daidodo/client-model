#ifndef DOZERG_SRC_LANGUAGE_H_20081126
#define DOZERG_SRC_LANGUAGE_H_20081126

#include <vector>
#include <string>

//�汾��Ϣ
//version info
#define SRC_version "1.1.94"

//��ʼ������
//init environment
void SRC_init();

//����Դ�ļ�
//compile source file
bool SRC_compile(const std::string & filename);

//����ִ��
//interpret and run
bool SRC_run();

//ע���Զ��庯��
//register user-defined function
bool SRC_register_function(const std::string & func_name,
    bool (*func_ptr)(std::vector<char> & src,std::vector<char> & dst));

#endif
