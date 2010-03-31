#ifndef DOZERG_CONFIG_H_20081113
#define DOZERG_CONFIG_H_20081113

#ifdef NDEBUG
#   define __LEXICAL_DEBUG 0
#   define __SYNTAX_DEBUG  0
#   define __RUNTIME_DEBUG 0
const int MAX_ERRORS = 3;
#else
//print lexical debug info
#   define __LEXICAL_DEBUG 0
//print syntax debug info
#   define __SYNTAX_DEBUG  0
//print runtime debug info
#   define __RUNTIME_DEBUG 0
#endif

//establish real connection
#define __REAL_CONNECT  1
//show results
#define __SHOW_RESULTS  1

const int MAX_ERRORS = 0;
#endif
