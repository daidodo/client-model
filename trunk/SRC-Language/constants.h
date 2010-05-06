#ifndef DOZERG_DATA_TYPES_H_20090203
#define DOZERG_DATA_TYPES_H_20090203

// data types that SRC supported
const int DT_NONE = -1;     //none
const int DT_VOID = 0;      //void
const int DT_INT =  1;      //int
const int DT_LONG = 2;      //long
const int DT_I64 =  3;      //i64
const int DT_U8 =   4;      //U8
const int DT_S8 =   5;      //S8
const int DT_U16 =  6;      //U16
const int DT_S16 =  7;      //S16
const int DT_U32 =  8;      //U32
const int DT_S32 =  9;      //S32
const int DT_U64 =  10;     //U64
const int DT_S64 =  DT_I64; //S64
const int DT_STR =  11;     //STR
const int DT_RAW =  12;     //RAW
const int DT_TCP =  13;     //TCP
const int DT_UDP =  14;     //UDP
const int DT_PA =   15;     //program argument
const int DT_STR1 = 16;     //STR1
const int DT_STR2 = DT_STR; //STR2
const int DT_STR4 = 18;     //STR4

inline bool DT_IsVoid(int type){return type == DT_VOID;}

inline bool DT_IsTcp(int type){return type == DT_TCP;}

inline bool DT_IsUdp(int type){return type == DT_UDP;}

inline bool DT_IsConnection(int type){return DT_IsTcp(type) || DT_IsUdp(type);}

inline bool DT_IsInteger(int type){return type >= DT_INT && type <= DT_U64;}

inline bool DT_IsSigned(int type){
    return (type == DT_INT ||
        type == DT_LONG ||
        type == DT_I64 ||
        type == DT_S8 ||
        type == DT_S16 ||
        type == DT_S32 ||
        type == DT_S64);
}

inline bool DT_IsUnsigned(int type){
    return (type == DT_U8 ||
        type == DT_U16 ||
        type == DT_U32 ||
        type == DT_U64);
}

inline bool DT_IsChar(int type){return type == DT_U8 || type == DT_S8;}

inline bool DT_IsString(int type){return type == DT_STR1 || type == DT_STR2 || type == DT_STR4 || type == DT_RAW;}

inline bool DT_IsRaw(int type){return type == DT_RAW;}

inline bool DT_IsProgArg(int type){return type == DT_PA;}

//extends:
inline bool DT_IsIntOrPA(int type){return DT_IsInteger(type) || DT_IsProgArg(type);}

inline bool DT_IsStrOrPA(int type){return DT_IsString(type) || DT_IsProgArg(type);}


// return values for assertions
const int RET_FALSE = 0;             //assert false
const int RET_TRUE = 1;              //assert true
const int RET_SIGN_MISMATCH = -1;    //signed, unsigned mismatch
const int RET_TYPE_ERROR = -2;       //argument type error
const int RET_OP_ERROR = -3;         //operator error

#endif
