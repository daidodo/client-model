#ifndef DOZERG_SRC_LANGUAGE_H_20081126
#define DOZERG_SRC_LANGUAGE_H_20081126

//src : Input buffer(���뻺��)
//src_len : Length of src(���뻺��ĳ���)
//dst : Output buffer(�������)
//src_len : Init and return length of dst(�������ĳ�ʼ���Ȳ������ͽ�����ȵķ���ֵ)
typedef bool (*__SRC_UserFunc)(const char * src,unsigned int src_len,char * dst,unsigned int & dst_len);

//�汾��Ϣ
//version info
#define SRC_version "2.1.153"

//��ʼ������
//init environment
void SRC_init();

//����Դ�ļ�
//compile source file
bool SRC_compile(const char * filename);

//����ִ��
//interpret and run
bool SRC_run(int argc,const char * const * argv);

//ע���Զ��庯��
//register user-defined function
bool SRC_register_function(const char * func_name
    , __SRC_UserFunc func_ptr
    , unsigned int dst_len_max = 65536);

#endif
