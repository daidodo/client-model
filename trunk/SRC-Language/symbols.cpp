#include "global.h"
#include "mm.h"
#include "dbg.h"
#include "util.h"
#include "tokens.h"

//CFixValue
CFixValue::CFixValue(int ln)
    : lineno_(ln)
    , type_(0)
    , int_(0)
    , long_(0)
    , i64_(0)
    , strIdx_(0)
{}

std::string CFixValue::ToString() const{
    std::ostringstream oss;
    oss<<"(type_="<<type_
        <<",int_="<<int_
        <<",long_="<<long_
        <<",i64_="<<i64_
        <<",strIdx_="<<strIdx_
        <<")";
    return oss.str();
}

std::string CFixValue::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")";
    return oss.str();
}

//CValue
CValue::CValue()
    : type_(0)
    , u64_(0)
{}

bool CValue::FromFixValue(const CFixValue & fv)
{
    switch(fv.type_){
        case 1:
            type_ = 1;
            int_ = fv.int_;
            break;
        case 2:
            type_ = 2;
            long_ = fv.long_;
            break;
        case 3:
            type_ = 9;
            s64_ = fv.i64_;
            break;
        case 4:
            type_ = 11;
            strIdx_ = fv.strIdx_;
            break;
        default:
            return false;
    }
    return true;
}

void CValue::FromVar(const CVariable & var,int lineno)
{
    if(var.IsArray()){
        GAMMAR_ERR(lineno,"cannot evaluate array, see LINE:"<<var.lineno_);
        return;
    }
    CSharedPtr<CDeclare> decl = runtime().FindVar(var.varname_);
    if(!decl){
        GAMMAR_ERR(lineno,"variable '"<<var.varname_
            <<"' not found(internal error)");
        return;
    }
    if(!decl->val_){
        GAMMAR_ERR(lineno,"variable '"<<var.varname_
            <<"' not initialized yet");
        return;
    }
    *this = *decl->val_;
}

//CVariable
CVariable::CVariable(int ln)
    : lineno_(ln)
    , type_(0)
    , simple_type_(0)
    , ref_count_(0)
{}

std::string CVariable::ToString() const{
    std::ostringstream oss;
    oss<<"(varname_="<<varname_
        <<",type_="<<type_
        <<",simple_type_="<<simple_type_
        <<",array_type_="<<signa(array_type_)
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
{}

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

bool CExpr::CheckDefined(int lineno) const
{
    if(func_call_)
        return func_call_->CheckDefined();
    if(var_ && var_->Is1stDefine()){
        GAMMAR_ERR(lineno,"undefined symbol '"<<var_->varname_<<"'");
        CUR_VTB.erase(var_->varname_);
        return false;
    }
    return true;
}

CSharedPtr<CValue> CExpr::Evaluate() const
{
    CSharedPtr<CValue> ret = New<CValue>();
    switch(type_){      //fix value
        case 1:
            assert(fix_value_);
            if(!ret->FromFixValue(*fix_value_)){
                GAMMAR_ERR(lineno_,"invalid fixed value(internal error)");
            }
            break;
        case 2:
            assert(func_call_);
            return func_call_->Evaluate();
            break;
        case 3:
            assert(var_);
            ret->FromVar(*var_,lineno_);
            break;
        default:
            return 0;
    }
    return ret;
}

//CArgList
CArgList::CArgList(int ln)
    : lineno_(ln)
{}

CSharedPtr<CExpr> CArgList::operator [](size_t i) const{
    assert(i < args_.size());
    return args_[i];
}

void CArgList::Add(CSharedPtr<CExpr> arg){
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

bool CArgList::CheckDefined(int lineno) const
{
    bool ret = true;
    for(size_t i = 0;i < args_.size();++i)
        ret = (args_[i]->CheckDefined(lineno) && ret);
    return ret;
}

//CArrayType
CArrayType::CArrayType(int ln)
    : lineno_(ln)
    , simple_type_(0)
{}

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

bool CArrayType::CheckDefined(int lineno) const
{
    if(expr_)
        return expr_->CheckDefined(lineno);
}

//CAssertExp
CAssertExp::CAssertExp(int ln)
    : lineno_(ln)
    , op_token_(0)
    , result_(false)
{}

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

bool CAssertExp::CheckDefined() const
{
    bool ret = true;
    if(expr1_)
        ret = expr1_->CheckDefined(lineno_);
    if(expr2_)
        ret = (expr2_->CheckDefined(lineno_) && ret);
    return ret;
}

//CDeclare
CDeclare::CDeclare(int ln)
    : lineno_(ln)
    , type_(0)
    , is_def_(0)
    , op_token(0)
    , simple_type(0)
{}

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
    if(var_->array_type_ && CannotBeArray(var_->array_type_->simple_type_)){
        GAMMAR_ERR(lineno_,"invaid array type");
    }else if(IsAssert() && !IsBinaryPredict(op_token)){
        GAMMAR_ERR(lineno_,"prediction format error");
        return false;
    }else
        return true;
    return false;
}

bool CDeclare::CheckDefined(CSharedPtr<CCmd> cur_cmd)
{
    bool ret = true;
    CSharedPtr<CVariable>& shadow = var_->shadow_;
    if(shadow){
        --shadow->ref_count_;
        if(cur_cmd == shadow->host_cmd_){
            GAMMAR_ERR(lineno_,"redefine symbol '"<<var_->varname_
                <<"', see LINE:"<<shadow->lineno_);
            var_ = shadow;
            ret = false;
        }else
            shadow = 0;
    }
    if(expr_)
        ret = (expr_->CheckDefined(lineno_) && ret);
    return ret;
}

//CFuncCall
CFuncCall::CFuncCall(int ln)
    : lineno_(ln)
    , ft_token_(0)
{}

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

bool CFuncCall::CheckDefined() const
{
    if(FunNeedNotCheckDefine(ft_token_))
        return true;
    if(arg_list_)
        return arg_list_->CheckDefined(lineno_);
    return true;
}

bool CFuncCall::Validate() const
{
    if(!FunArgNumCheck(ft_token_,(arg_list_ ? arg_list_->args_.size() : 0))){
        GAMMAR_ERR(lineno_,"number of args is invalid");
        return false;
    }
    return true;
}

CSharedPtr<CValue> CFuncCall::Evaluate() const
{
    
}

//CStmt
CStmt::CStmt(int ln)
    : lineno_(ln)
    , type_(0)
{}

std::string CStmt::ToString() const{
    std::ostringstream oss;
    oss<<"(type_="<<type_
        <<",assert_="<<signa(assert_)
        <<",declare_="<<signa(declare_)
        <<",func_call_="<<signa(func_call_)
        <<",cmd_="<<signa(cmd_)
        <<")";
    return oss.str();
}

std::string CStmt::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")";
    return oss.str();
}

//CCmd
CCmd::CCmd(int ln)
    : lineno_(ln)
{}

std::string CCmd::ToString() const{
    std::ostringstream oss;
    oss<<"(cmd_name_="<<cmd_name_;
    for(size_t i = 0;i < stmt_list_.size();++i)
        oss<<",stmt_list_["<<i<<"]="<<signa(stmt_list_[i]);
    oss<<")";
    return oss.str();
}

std::string CCmd::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")"<<cmd_name_;
    return oss.str();
}

