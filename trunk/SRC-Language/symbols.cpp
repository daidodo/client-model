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

int CFixValue::RetType() const
{
    switch(type_){
        case 1:return 1;
        case 2:return 2;
        case 3:return 9;
        case 4:return 11;
    }
    return -1;
}

CSharedPtr<CValue> CFixValue::Evaluate(int lineno) const
{
    CSharedPtr<CValue> ret = New<CValue>();
    switch(type_){
        case 1:
            ret->type_ = 1;
            ret->int_ = int_;
            break;
        case 2:
            ret->type_ = 2;
            ret->long_ = long_;
            break;
        case 3:
            ret->type_ = 9;
            ret->s64_ = i64_;
            break;
        case 4:
            ret->type_ = 11;
            ret->str_ = program().GetQstr(strIdx_);
            break;
        default:
            GAMMAR_ERR(lineno,"invalid fixed value(internal error)");
            return 0;
    }
    return ret;
}

//CVariable
CVariable::CVariable(int ln)
    : lineno_(ln)
    , type_(0)
    , tp_token_(0)
    , ref_count_(0)
    , begin_(-1)
{}

std::string CVariable::ToString() const{
    std::ostringstream oss;
    oss<<"(varname_="<<varname_
        <<",type_="<<type_
        <<",tp_token_="<<tp_token_
        <<",array_type_="<<signa(array_type_)
        <<",ref_count_="<<ref_count_
        <<",host_cmd_="<<signa(host_cmd_)
        <<",shadow_="<<to_str(shadow_)
        <<",begin_="<<begin_
        <<")";
    return oss.str();
}

std::string CVariable::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")"<<varname_;
    return oss.str();
}

bool CVariable::IsConnection() const
{
    return IsConnectionToken(tp_token_);
}

bool CVariable::IsRaw() const
{
    return IsRawToken(tp_token_);
}

int CVariable::RetType() const
{
    return (array_type_ ? array_type_->RetType() : FunRetType(tp_token_));
}

CSharedPtr<CValue> CVariable::Evaluate(int lineno) const
{
    if(array_type_){
        GAMMAR_ERR(lineno,"cannot evaluate array, see LINE:"<<lineno_);
        return 0;
    }
    CSharedPtr<CDeclare> decl = runtime().FindVar(varname_);
    if(!decl){
        GAMMAR_ERR(lineno,"variable '"<<varname_
            <<"' not found(internal error)");
        return 0;
    }
    if(!decl->val_){
        GAMMAR_ERR(lineno,"variable '"<<varname_
            <<"' not initialized yet");
        return 0;
    }
    return decl->val_;
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

bool CExpr::Validate() const
{
    if(func_call_ && !func_call_->Validate())
        return false;
    return true;
}

int CExpr::RetType() const
{
    switch(type_){
        case 1:
            assert(fix_value_);
            return fix_value_->RetType();
        case 2:
            assert(func_call_);
            return func_call_->RetType();
        case 3:
            assert(var_);
            return var_->RetType();
    }
    return -1;
}

CSharedPtr<CValue> CExpr::Evaluate() const
{
    switch(type_){
        case 1:
            assert(fix_value_);
            return fix_value_->Evaluate(lineno_);
        case 2:
            assert(func_call_);
            return func_call_->Evaluate();
        case 3:
            assert(var_);
            return var_->Evaluate(lineno_);
    }
    return 0;
}

std::string CExpr::Depend() const
{
    if(func_call_)
        return func_call_->Depend();
    else if(var_ && runtime().IsPost(var_->varname_))
        return var_->varname_;
    return "";
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

bool CArgList::Validate() const
{
    for(size_t i = 0;i < args_.size();++i)
        if(!args_[i]->Validate())
            return false;
    return true;
}

void CArgList::RetType(std::vector<int> & ret) const
{
    ret.resize(args_.size());
    for(size_t i = 0;i < args_.size();++i)
        ret[i] = args_[i]->RetType();
}

bool CArgList::Evaluate(std::vector<CSharedPtr<CValue> > & ret,int lineno) const
{
    ret.resize(args_.size());
    for(size_t i = 0;i < args_.size();++i){
        ret[i] = args_[i]->Evaluate();
        if(!ret[i]){
            GAMMAR_ERR(lineno,"cannot evaluate argument "<<(i + 1));
            return false;
        }
    }
    return true;
}

std::string CArgList::Depend() const
{
    std::string ret;
    double pri = 0;
    for(size_t i = 0;i < args_.size();++i){
        std::string vname = args_[i]->Depend();
        double vp = runtime().Priority(vname);
        if(vp > pri){
            ret = vname;
            pri = vp;
        }
    }
    return ret;
}

//CArrayType
CArrayType::CArrayType(int ln)
    : lineno_(ln)
    , tp_token_(0)
    , sz_(-1)
{}

std::string CArrayType::ToString() const{
    std::ostringstream oss;
    oss<<"(tp_token_="<<tp_token_
        <<",sz_="<<sz_
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

int CArrayType::RetType() const
{
    return FunRetType(tp_token_);
}

//CAssertExp
CAssertExp::CAssertExp(int ln)
    : lineno_(ln)
    , op_token_(0)
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
        return false;
    }
    if(IsUnaryPredict(op_token_) && expr2_){
        GAMMAR_ERR(lineno_,"prediction format error(unary)");
        return false;
    }
    if(!expr1_->Validate())
        return false;
    if(expr2_ && !expr2_->Validate())
        return false;
    return true;
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
    , op_token_(0)
    , eva_priority_(0)
    , offset_(-1)
{}

std::string CDeclare::ToString() const{
    std::ostringstream oss;
    oss<<"(type_="<<type_
        <<",is_def_="<<is_def_
        <<",var_="<<signa(var_)
        <<",op_token_="<<op_token_
        <<",expr_="<<signa(expr_)
        <<",eva_priority_="<<eva_priority_
        <<",val_="<<signa(val_)
        <<")";
    return oss.str();
}

std::string CDeclare::Signature() const{
    return signa(var_);
}

bool CDeclare::IsGlobalOnly() const
{
    return IsGlobalOnlyToken(var_->tp_token_);
}

bool CDeclare::Validate() const
{
    if(var_->array_type_ && CannotBeArray(var_->array_type_->tp_token_)){
        GAMMAR_ERR(lineno_,"invaid array type");
        return false;
    }
    if(IsAssert() && !IsBinaryPredict(op_token_)){
        GAMMAR_ERR(lineno_,"prediction format error");
        return false;
    }
    if(expr_ && !expr_->Validate())
        return false;
    return true;
}

bool CDeclare::IsStreamIn() const
{
    return (IsStream() && IsStreamInToken(op_token_));
}

bool CDeclare::IsStreamOut() const
{
    return (IsStream() && IsStreamOutToken(op_token_));
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

void CDeclare::FixRaw()
{
    assert(val_ && var_);
    if(var_->IsRaw())
        val_->FixRaw();
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
    if(arg_list_ && !arg_list_->Validate())
        return false;
    if(!FunArgNumCheck(ft_token_,(arg_list_ ? arg_list_->args_.size() : 0))){
        GAMMAR_ERR(lineno_,"number of args is invalid");
        return false;
    }
    std::vector<int> retTypes;
    if(arg_list_)
        arg_list_->RetType(retTypes);
    size_t i = FunArgTypeCheck(ft_token_,retTypes,arg_list_);
    if(i){
        GAMMAR_ERR(lineno_,"type or variable mismatch for argument "<<i);
        return false;
    }
    return true;
}

bool CFuncCall::IsConnection() const
{
    return IsConnectionToken(ft_token_);
}

bool CFuncCall::IsGlobalOnly() const
{
    return IsGlobalOnlyToken(ft_token_);
}

bool CFuncCall::IsLocalOnly() const
{
    return IsLocalOnlyToken(ft_token_);
}

int CFuncCall::RetType() const
{
    return FunRetType(ft_token_);
}

std::string CFuncCall::Depend() const
{
    if(arg_list_)
        return arg_list_->Depend();
    return "";
}

int CFuncCall::IsSendRecv() const
{
    return IsSendRecvToken(ft_token_);
}

CSharedPtr<CValue> CFuncCall::Evaluate() const
{
    std::vector<CSharedPtr<CValue> > args;
    if(arg_list_){
        if(!arg_list_->Evaluate(args,lineno_))
            return 0;
    }
    return FunEvaluate(ft_token_,args,lineno_);
}

void CFuncCall::Invoke(CSharedPtr<CCmd> cmd) const
{
    FunInvoke(ft_token_,arg_list_,lineno_,cmd);
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
    , send_flag_(0)
    , inds_(recv_data_)
{}

std::string CCmd::ToString() const{
    std::ostringstream oss;
    oss<<"(cmd_name_="<<cmd_name_
        <<",send_flag_="<<send_flag_;
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

void CCmd::SetByteOrder(bool net_bo)
{

}

void CCmd::AddConnection(CSharedPtr<CValue> conn,int lineno)
{
    assert(conn && conn->IsConnection());
    if(!conn_list_.empty()){
        RUNTIME_ERR(lineno,"only one connction is supported for one command");
    }else
        conn_list_.push_back(conn);
}

bool CCmd::SendValue(CSharedPtr<CValue> v)
{
    assert(v);
    return (outds_<<*v);
}
