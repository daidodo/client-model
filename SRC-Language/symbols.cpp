#include "global.h"
#include "mm.h"
#include "dbg.h"
#include "errors.h"
#include "util.h"
#include "tokens.h"

//CFixValue
CFixValue::CFixValue(int ln)
    : lineno_(ln)
    , type_(0)
    , number_(0)
    , strIdx_(0)
{}

std::string CFixValue::ToString() const{
    std::ostringstream oss;
    oss<<"(type_="<<type_
        <<",number_="<<number_
        <<",strIdx_="<<strIdx_
        <<")";
    return oss.str();
}

std::string CFixValue::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")";
    return oss.str();
}

//CTcp
CTcp::CTcp(int ln)
    :   lineno_(ln)
{}

std::string CTcp::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")";
    return oss.str();
}

//CUdp
CUdp::CUdp(int ln)
    : lineno_(ln)
{}

std::string CUdp::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")";
    return oss.str();
}

//CVariable
CVariable::CVariable(int ln)
    : lineno_(ln)
    , type_(0)
    , simple_type_(0)
    , ref_count_(0)
    , array_type_(0)
    , host_cmd_(0)
    , shadow_(0)
{}

CVariable::~CVariable(){
    Delete(array_type_);
}

std::string CVariable::ToString() const{
    std::ostringstream oss;
    oss<<"(varname_="<<varname_
        <<",type_="<<type_
        <<",simple_type_="<<simple_type_
        <<",array_type_="<<signa(array_type_)
        <<",val_.size()="<<val_.size()
        <<",ref_count_="<<ref_count_
        <<",host_cmd_="<<signa(host_cmd_)
        <<",shadow_="<<to_str(shadow_)
        <<")";
    return oss.str();
}

std::string CVariable::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")"<<varname_;
    return oss.str();
}

//CExpr
CExpr::CExpr(int ln)
    : lineno_(ln)
    , type_(0)
    , fix_value_(0)
    , func_call_(0)
    , var_(0)
{}

CExpr::~CExpr(){
    Delete(fix_value_);
    Delete(func_call_);
    Delete(var_);
}

std::string CExpr::ToString() const{
    std::ostringstream oss;
    oss<<"(type_="<<type_
        <<",fix_value_="<<signa(fix_value_)
        <<",func_call_="<<signa(func_call_)
        <<",var_="<<signa(var_)
        <<")";
    return oss.str();
}

std::string CExpr::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")";
    return oss.str();
}

//CArrayType
CArrayType::CArrayType(int ln)
    : lineno_(ln)
    , simple_type_(0)
    , expr_(0)
{}

CArrayType::~CArrayType(){
    Delete(expr_);
}

std::string CArrayType::ToString() const{
    std::ostringstream oss;
    oss<<"(simple_type_="<<simple_type_
        <<",expr_="<<signa(expr_)
        <<")";
    return oss.str();
}

std::string CArrayType::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")";
    return oss.str();
}

//CAssertExp
CAssertExp::CAssertExp(int ln)
    : lineno_(ln)
    , op_token_(0)
    , expr1_(0)
    , expr2_(0)
{}

CAssertExp::~CAssertExp(){
    Delete(expr1_);
    Delete(expr2_);
}

std::string CAssertExp::ToString() const{
    std::ostringstream oss;
    oss<<"(op_token_="<<op_token_
        <<",expr1_="<<signa(expr1_)
        <<",expr2_="<<signa(expr2_)
        <<")";
    return oss.str();
}

std::string CAssertExp::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")";
    return oss.str();
}

bool CAssertExp::Validate() const
{
    assert(expr1_);
    if(IsBinaryPredict(op_token_) && !expr2_){
        GAMMAR_ERR(lineno_,"prediction format error(binary)");
    }else if(IsUnaryPredict(op_token_) && expr2_){
        GAMMAR_ERR(lineno_,"prediction format error(unary)");
    }else
        return true;
    return false;
}

//CDeclare
CDeclare::CDeclare(int ln)
    : lineno_(ln)
    , type_(0)
    , is_def_(0)
    , op_token(0)
    , simple_type(0)
    , var_(0)
    , expr_(0)
{}

CDeclare::~CDeclare(){
    Delete(var_);
    Delete(expr_);
}

std::string CDeclare::ToString() const{
    std::ostringstream oss;
    oss<<"(type_="<<type_
        <<",var_="<<signa(var_)
        <<",op_token="<<op_token
        <<",expr_="<<signa(expr_)
        <<",simple_type="<<simple_type
        <<")";
    return oss.str();
}

std::string CDeclare::Signature() const{
    return signa(var_);
}

bool CDeclare::IsGlobalOnly() const
{
    if(var_->array_type_)
        return IsOnlyGlobalType(var_->array_type_->simple_type_);
    return IsOnlyGlobalType(var_->simple_type_);
}

bool CDeclare::Validate() const
{
    //array type check
    if(var_->array_type_ && CannotBeArray(var_->array_type_->simple_type_)){
        GAMMAR_ERR(lineno_,"error array type");
    }else if(IsAssert() && !IsBinaryPredict(op_token)){
        GAMMAR_ERR(lineno_,"prediction format error");
        return false;
    }else
        return true;
    return false;
}

//CArgList
CArgList::CArgList(int ln)
    : lineno_(ln)
{}

CArgList::~CArgList(){
    std::for_each(args_.begin(),args_.end(),Delete<CExpr>);
}

CExpr * CArgList::operator [](size_t i) const{
    assert(i < args_.size());
    return args_[i];
}

void CArgList::Add(CExpr * arg){
    args_.push_back(arg);
}

std::string CArgList::ToString() const{
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

std::string CArgList::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")";
    return oss.str();
}

//CFuncCall
CFuncCall::CFuncCall(int ln)
    : lineno_(ln)
    , ft_token_(0)
    , arg_list_(0)
{}

CFuncCall::~CFuncCall(){
    Delete(arg_list_);
}

std::string CFuncCall::ToString() const{
    std::ostringstream oss;
    oss<<"(ft_token_="<<ft_token_
        <<",arg_list_="<<signa(arg_list_)
        <<")";
    return oss.str();
}

std::string CFuncCall::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")"<<ft_token_;
    return oss.str();
}

//CStmt
CStmt::CStmt(int ln)
    : lineno_(ln)
    , type_(0)
    , assert_(0)
{}

CStmt::~CStmt(){
    Delete(assert_);
    Delete(declare_);
    Delete(func_call_);
}

std::string CStmt::ToString() const{
    std::ostringstream oss;
    oss<<"(type_="<<type_
        <<",assert_="<<signa(assert_)
        <<",declare_="<<signa(declare_)
        <<",func_call_="<<signa(func_call_)
        <<")";
    return oss.str();
}

std::string CStmt::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")";
    return oss.str();
}

//CCommand
CCommand::CCommand(int ln)
    : lineno_(ln)
{}

CCommand::~CCommand(){
    for(__VarTable::iterator i = var_table.begin();i != var_table.end();++i)
        Delete(i->second);
    std::for_each(stmt_list_.begin(),stmt_list_.end(),Delete<CStmt>);
}

std::string CCommand::ToString() const{
    std::ostringstream oss;
    oss<<"(cmd_name_="<<cmd_name_;
    for(size_t i = 0;i < stmt_list_.size();++i)
        oss<<",stmt_list_["<<i<<"]="<<signa(stmt_list_[i]);
    oss<<")";
    return oss.str();
}

std::string CCommand::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")"<<cmd_name_;
    return oss.str();
}

