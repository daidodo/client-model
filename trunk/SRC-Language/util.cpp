#include <cassert>  //assert
#include <cstddef>  //size_t
#include <cstdlib>  //atoi
#include "util.h"

int str2int(const char * str,size_t len)
{
    assert(str && len);
    int ret = atoi(str);
    switch(str[len - 1]){
        case 'k':case 'K':
            ret <<= 10;
            break;
        case 'm':case 'M':
            ret <<= 20;
            break;
        case 'g':case 'G':
            ret <<= 30;
            break;
        default:;
    }
    return ret;
}

//int qstr(std::string & res,const char * src,size_t len)
//{
//    assert(src && len);
//    res.clear();
//    int nl = 0;
//    int state = 0;
//    for(const char * end = src + len;src < end;++src){
//        switch(state){
//            case 0:{
//                if(*src != '\"')
//                    return -1;
//                state = 1;
//                break;}
//            case 1:{
//                if(*src == '\"')
//                    state = 2;
//                else if(*src == '\\')
//                    state = 3;
//                else if(*src == '\n')
//                    return -1;
//                else
//                    res.push_back(*src);
//                break;}
//            case 2:{
//                if(src != end)
//                    return -1;
//                break;}
//            case 3:{
//                state = 1;
//                switch(*src){
//                    case 'a':res.push_back('\a');break;
//                    case 'b':res.push_back('\b');break;
//                    case 't':res.push_back('\t');break;
//                    case 'n':res.push_back('\n');break;
//                    case 'v':res.push_back('\v');break;
//                    case 'f':res.push_back('\f');break;
//                    case 'r':res.push_back('\r');break;
//                    case '0':res.push_back('\0');break;
//                    case '\n':++nl;break;
//                    case '\r':state = 4;break;
//                    default:res.push_back(*src);
//                }
//                break;}
//            case 4:{
//                if(*src == '\n'){
//                    state = 1;
//                    ++nl;
//                }else
//                    return -1;
//                break;}
//            default:
//                return -1;
//        }
//    }
//    return nl;
//}

int atoi_base8(const char * str,size_t len)
{
    assert(str && len);
    int ret = 0;
    for(size_t i = 0;i < len;++i){
        assert(str[i] >= '0' && str[i] <= '7');
        ret = (ret << 3) + str[i] - '0';
    }
    return ret;
}

int atoi_base16(const char * str,size_t len)
{
    assert(str && len);
    int ret = 0;
    for(size_t i = 0;i < len;++i){
        ret <<= 4;
        if(str[i] >= '0' && str[i] <= '9')
            ret += str[i] - '0';
        else if(str[i] >= 'a' && str[i] <= 'f')
            ret += str[i] - 'a' + 10;
        else if(str[i] >= 'A' && str[i] <= 'F')
            ret += str[i] - 'A' + 10;
        else
            assert(0);
    }
    return ret;
}
