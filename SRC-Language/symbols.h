#ifndef DOZERG_SYMBOLS_H_20081111
#define DOZERG_SYMBOLS_H_20081111

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>
#include "types.h"
#include "mm.h"
#include "util.h"

struct CFixValue
{
    const int lineno_;
    int type_;
    int number_;
    size_t strIdx_;
    //functions:
    explicit CFixValue(int ln):lineno_(ln),type_(0),number_(0),strIdx_(0){}
    std::string ToString() const{
        std::ostringstream oss;
        oss<<"(type_="<<type_
            <<",number_="<<number_
            <<",strIdx_="<<strIdx_
            <<")";
        return oss.str();
    }
    std::string Signature() const{
        std::ostringstream oss;
        oss<<"(LINE:"<<lineno_<<")";
        return oss.str();
    }
};

struct CTcp
{
};

struct CUdp
{
};

struct CValue
{
    union{
        U8  u8_;
        S8  s8_;
        U16 u16_;
        S16 s16_;
        U32 u32_;
        S32 s32_;
        U64 u64_;
        S64 s64_;
        size_t strIdx_;
        CTcp * tcp_;
        CUdp * udp_;
    };
    //functions:
    CValue():u64_(0){}
};

struct CArrayType;

struct CVariable
{
    std::string varname_;
    const int lineno_;
    int type_;
    int simple_type_;
    CArrayType * array_type_;
    std::vector<CValue> val_;
    //functions:
    explicit CVariable(int ln):lineno_(ln),type_(0),simple_type_(0),array_type_(0){}
    ~CVariable(){
        Delete(array_type_);
    }
    std::string ToString() const{
        std::ostringstream oss;
        oss<<"(varname_="<<varname_
            <<",type_="<<type_
            <<",simple_type_="<<simple_type_
            <<",array_type_="<<signa(array_type_)
            <<",val_.size()="<<val_.size()
            <<")";
        return oss.str();
    }
    std::string Signature() const{
        return varname_;
    }
};

struct CFuncCall;

struct CExpr
{
    const int lineno_;
    int type_;
    CFixValue * fix_value_;
    CFuncCall * func_call_;
    CVariable * var_;
    //functions:
    explicit CExpr(int ln):lineno_(ln),type_(0),fix_value_(0),func_call_(0),var_(0){}
    ~CExpr(){
        Delete(fix_value_);
        Delete(func_call_);
        Delete(var_);
    }
    std::string ToString() const{
        std::ostringstream oss;
        oss<<"(type_="<<type_
            <<",fix_value_="<<signa(fix_value_)
            <<",func_call_="<<signa(func_call_)
            <<",var_="<<signa(var_)
            <<")";
        return oss.str();
    }
    std::string Signature() const{
        std::ostringstream oss;
        oss<<"(LINE:"<<lineno_<<")";
        return oss.str();
    }
};

struct CArrayType
{
    const int lineno_;
    int simple_type_;
    CExpr * expr_;
    //functions:
    explicit CArrayType(int ln):lineno_(ln),simple_type_(0),expr_(0){}
    ~CArrayType(){
        Delete(expr_);
    }
    std::string ToString() const{
        std::ostringstream oss;
        oss<<"(simple_type_="<<simple_type_
            <<",expr_="<<signa(expr_)
            <<")";
        return oss.str();
    }
    std::string Signature() const{
        std::ostringstream oss;
        oss<<"(LINE:"<<lineno_<<")";
        return oss.str();
    }
};

struct CAssertExp
{
    const int lineno_;
    int op_token_;
    CExpr * expr1_;
    CExpr * expr2_;
    //functions:
    explicit CAssertExp(int ln):lineno_(ln),op_token_(0),expr1_(0),expr2_(0){}
    ~CAssertExp(){
        Delete(expr1_);
        Delete(expr2_);
    }
    std::string ToString() const{
        std::ostringstream oss;
        oss<<"(op_token_="<<op_token_
            <<",expr1_="<<signa(expr1_)
            <<",expr2_="<<signa(expr2_)
            <<")";
        return oss.str();
    }
    std::string Signature() const{
        std::ostringstream oss;
        oss<<"(LINE:"<<lineno_<<")";
        return oss.str();
    }
};

struct CSimDeclare
{
    const int lineno_;
    int type_;
    int is_def_;
    int op_token;
    int simple_type;
    CVariable * var_;
    CExpr * expr_;
    //functions:
    explicit CSimDeclare(int ln)
        : lineno_(ln)
        , type_(0)
        , is_def_(0)
        , op_token(0)
        , simple_type(0)
        , var_(0)
        , expr_(0)
    {}
    ~CSimDeclare(){
        Delete(var_);
        Delete(expr_);
    }
    std::string ToString() const{
        std::ostringstream oss;
        oss<<"(type_="<<type_
            <<",var_="<<signa(var_)
            <<",op_token="<<op_token
            <<",expr_="<<signa(expr_)
            <<",simple_type="<<simple_type
            <<")";
        return oss.str();
    }
    std::string Signature() const{
        return signa(var_);
    }
};

struct CArgList
{
    const int lineno_;
    std::vector<CExpr *> args_;
    //fuctions:
    explicit CArgList(int ln):lineno_(ln){}
    ~CArgList(){
        std::for_each(args_.begin(),args_.end(),Delete<CExpr>);
    }
    CExpr * operator [](size_t i) const{
        assert(i < args_.size());
        return args_[i];
    }
    void Add(CExpr * arg){
        args_.push_back(arg);
    }
    std::string ToString() const{
        std::ostringstream oss;
        oss<<"(";
        if(!args_.empty()){
            oss<<"args_[0]="<<signa(args_[0]);
            for(size_t i = 1;i < args_.size();++i)
                oss<<",args_["<<i<<"]="<<signa(args_[i]);
        }
        oss<<")";
        return oss.str();
    }
    std::string Signature() const{
        std::ostringstream oss;
        oss<<"(LINE:"<<lineno_<<")";
        return oss.str();
    }
};

struct CFuncCall
{
    const int lineno_;
    int ft_token_;
    CArgList * arg_list_;
    //functions:
    explicit CFuncCall(int ln):lineno_(ln),ft_token_(0),arg_list_(0){}
    ~CFuncCall(){
        Delete(arg_list_);
    }
    std::string ToString() const{
        std::ostringstream oss;
        oss<<"(ft_token_="<<ft_token_
            <<"arg_list_="<<signa(arg_list_)
            <<")";
        return oss.str();
    }
    std::string Signature() const{
        std::ostringstream oss;
        oss<<"(LINE:"<<lineno_<<")"<<ft_token_;
        return oss.str();
    }
};

struct CStmt
{
    const int lineno_;
    int type_;
    CAssertExp * assert_;
    CSimDeclare * declare_;
    CFuncCall * func_call_;
    //functions:
    explicit CStmt(int ln):lineno_(ln),type_(0),assert_(0){}
    ~CStmt(){
        Delete(assert_);
        Delete(declare_);
        Delete(func_call_);
    }
    std::string ToString() const{
        std::ostringstream oss;
        oss<<"(type_="<<type_
            <<",assert_="<<signa(assert_)
            <<",declare_="<<signa(declare_)
            <<",func_call_="<<signa(func_call_)
            <<")";
        return oss.str();
    }
    std::string Signature() const{
        std::ostringstream oss;
        oss<<"(LINE:"<<lineno_<<")";
        return oss.str();
    }
};

struct CCommand
{
    const int lineno_;
    std::string cmd_name_;
    std::vector<CStmt *> items_;
    std::map<std::string,CVariable *> var_table;
    //functions:
    explicit CCommand(int ln):lineno_(ln){}
    ~CCommand(){
        std::for_each(items_.begin(),items_.end(),Delete<CStmt>);
        for(std::map<std::string,CVariable *>::iterator i = var_table.begin();i != var_table.end();++i)
            Delete(i->second);
    }
    std::string ToString() const{
        std::ostringstream oss;
        oss<<"(cmd_name_="<<cmd_name_;
        for(size_t i = 0;i < items_.size();++i)
            oss<<",items_["<<i<<"]="<<signa(items_[i]);
        oss<<")";
        return oss.str();
    }
    std::string Signature() const{
        return cmd_name_;
    }
};

#endif
