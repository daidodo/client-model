#ifndef DOZERG_TYPES_H_20081111
#define DOZERG_TYPES_H_20081111

#if defined(__GNUC__)
#   include <stdint.h>
//basic types
typedef int8_t              S8;
typedef uint8_t             U8;
typedef int16_t             S16;
typedef uint16_t            U16;
typedef int32_t             S32;
typedef uint32_t            U32;
typedef int64_t             S64;
typedef uint64_t            U64;
#elif defined(WIN32)
typedef __int8              S8;
typedef unsigned __int8     U8;
typedef __int16             S16;
typedef unsigned __int16    U16;
typedef __int32             S32;
typedef unsigned __int32    U32;
typedef __int64             S64;
typedef unsigned __int64    U64;
#else   //platform dependenty
typedef signed char         S8;
typedef unsigned char       U8;
typedef short               S16;
typedef unsigned short      U16;
typedef int                 S32;
typedef unsigned int        U32;
typedef long long           S64;
typedef unsigned long long  U64;
#endif

typedef unsigned int UINT;

#endif
