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
        <<",struct_name_="<<signa(struct_name_)
        <<",struct_type_="<<signa(struct_type_)
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
    if(IsStruct())
        return -1;
    else if(IsArray()){
        assert(array_type_);
        return array_type_->RetType();
    }else
        return FunRetType(tp_token_);
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

CSharedPtr<CValue> CVariable::Initial(int lineno) const
{
    if(IsStruct())
        return 0;
    if(array_type_)
        return array_type_->Evaluate();
    std::vector<CSharedPtr<CValue> > args;
    return FunEvaluate(tp_token_,args,lineno);
}

CSharedPtr<CVariable> CVariable::Copy() const
{
    CSharedPtr<CVariable> ret = New<CVariable>(lineno_);
    ret->type_ = type_;
    ret->tp_token_ = tp_token_;
    ret->ref_count_ = ref_count_;
    ret->begin_ = begin_;
    if(array_type_)
        ret->array_type_ = array_type_->Copy();
    ret->struct_name_ = struct_name_;
    ret->struct_type_ = struct_type_;
    ret->host_cmd_ = host_cmd_;
    //shadow_
    return ret;
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

CSharedPtr<CExpr> CExpr::Copy() const
{
    CSharedPtr<CExpr> ret = New<CExpr>(lineno_);
    ret->type_ = type_;
    ret->fix_value_ = fix_value_;
    if(func_call_)
        ret->func_call_ = func_call_->Copy();
    if(var_)
        ret->var_ = var_->Copy();
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

void CArgList::Erase(CSharedPtr<CExpr> arg)
{
    for(size_t i = 0;i < args_.size();++i){
        if(args_[i]->var_ == arg->var_)
            args_.erase(args_.begin() + i);         //性能损失的地方
    }
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

CSharedPtr<CArgList> CArgList::Copy() const
{
    CSharedPtr<CArgList> ret = New<CArgList>(lineno_);
    for(size_t i = 0;i < args_.size();++i)
        ret->args_.push_back(args_[i]->Copy());
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

bool CArrayType::Validate() const
{
    if(expr_ && !CValue::IsInteger(expr_->RetType())){
        GAMMAR_ERR(lineno_,"invalid type for array size");
        return false;
    }
    return true;
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

CSharedPtr<CValue> CArrayType::Evaluate() const
{
    std::vector<CSharedPtr<CValue> > args;
    return FunEvaluate(tp_token_,args,lineno_);
}

CSharedPtr<CArrayType> CArrayType::Copy() const
{
    CSharedPtr<CArrayType> ret = New<CArrayType>(lineno_);
    ret->tp_token_ = tp_token_;
    ret->sz_ = sz_;
    if(expr_)
        ret->expr_ = expr_->Copy();
    return ret;
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
    int type1 = expr1_->RetType();
    int type2 = 0;
    if(IsBinaryPredict(op_token_)){
        if(!expr2_){
            GAMMAR_ERR(lineno_,"prediction format error(binary)");
            return false;
        }
        type2 = expr2_->RetType();
    }else if(IsUnaryPredict(op_token_)){
        if(expr2_){
            GAMMAR_ERR(lineno_,"prediction format error(unary)");
            return false;
        }
    }else{
        GAMMAR_ERR(lineno_,"unknown prediction operator");
        return false;
    }
    size_t i = OpArgTypeCheck(op_token_,type1,type2);
    if(i){
        GAMMAR_ERR(lineno_,"invalid argument "<<i<<" for prediction");
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

bool CAssertExp::Assert() const
{
    assert(expr1_);
    CSharedPtr<CValue> v1 = expr1_->Evaluate();
    if(!v1){
        RUNTIME_ERR(lineno_,"cannot evaluate left hand expression");
        return false;
    }
    CSharedPtr<CValue> v2;
    if(expr2_){
        v2 = expr2_->Evaluate();
        if(!v2){
            RUNTIME_ERR(lineno_,"cannot evaluate right hand expression");
            return false;
        }
    }
    switch(FunAssert(op_token_,v1,v2)){
        case 0:break;
        case 1:return true;
        case -1:{
            RUNTIME_ERR(lineno_,"prediction between signed and unsigned integers");
            break;}
        case -2:{
            RUNTIME_ERR(lineno_,"invalid argument type for prediction");
            break;}
        case -3:{
            RUNTIME_ERR(lineno_,"invalid operator type for prediction");
            break;}
    }
    return false;
}

CSharedPtr<CAssertExp> CAssertExp::Copy() const
{
    CSharedPtr<CAssertExp> ret = New<CAssertExp>(lineno_);
    ret->op_token_ = op_token_;
    if(expr1_)
        ret->expr1_ = expr1_->Copy();
    if(expr2_)
        ret->expr2_ = expr2_->Copy();
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
    if(IsStruct() && !IsSimplePost() && !IsArray()){
        GAMMAR_ERR(lineno_,"invaid struct variable");
        return false;
    }
    if(IsArray()){
        if(!var_->array_type_->Validate())
            return false;
        if(CannotBeArray(var_->array_type_->tp_token_)){
            GAMMAR_ERR(lineno_,"invaid array type");
            return false;
        }
        if(is_def_){
            GAMMAR_ERR(lineno_,"invalid DEF for array type");
            return false;
        }
    }else if(IsAssert()){
        assert(expr_);
        if(!IsBinaryPredict(op_token_)){
            GAMMAR_ERR(lineno_,"prediction format error");
            return false;
        }
        size_t i = OpArgTypeCheck(op_token_,var_->RetType(),expr_->RetType());
        if(i){
            GAMMAR_ERR(lineno_,"argument "<<i<<" type error for prediction");
            return false;
        }
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

bool CDeclare::CheckDefined(CSharedPtr<CCmdStruct> cur_cmd)
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

CSharedPtr<CValue> CDeclare::Evaluate()
{
    if(expr_)
        val_ = expr_->Evaluate();
    if(!val_){
        RUNTIME_ERR(lineno_,"cannot evaluate '"<<var_->varname_
            <<"'");
    }else
        FixRaw();   //区分STR和RAW类型
    return val_;
}

CSharedPtr<CDeclare> CDeclare::Copy() const
{
    CSharedPtr<CDeclare> ret = New<CDeclare>(lineno_);
    ret->type_ = type_;
    ret->is_def_ = is_def_;
    ret->op_token_ = op_token_;
    ret->eva_priority_ = eva_priority_;
    ret->offset_ = offset_;
    if(var_)
        ret->var_ = var_->Copy();
    if(expr_)
        ret->expr_ = expr_->Copy();
    if(val_)
        ret->val_ = val_->Copy();
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
    if(!IsFunToken(ft_token_) && arg_list_)
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
    std::vector<int> retTypes;
    if(arg_list_)
        arg_list_->RetType(retTypes);
    return FunRetType(ft_token_,&retTypes);
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

void CFuncCall::Invoke(CSharedPtr<CCmdStruct> cmd) const
{
    FunInvoke(ft_token_,arg_list_,lineno_,cmd);
}

CSharedPtr<CFuncCall> CFuncCall::Copy() const
{
    CSharedPtr<CFuncCall> ret = New<CFuncCall>(lineno_);
    ret->ft_token_ = ft_token_;
    if(arg_list_)
        ret->arg_list_ = arg_list_->Copy();
    return ret;
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
        <<",cmd_struct_="<<signa(cmd_struct_)
        <<")";
    return oss.str();
}

std::string CStmt::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")";
    return oss.str();
}

CSharedPtr<CStmt> CStmt::Copy() const
{
    CSharedPtr<CStmt> ret = New<CStmt>(lineno_);
    ret->type_ = type_;
    if(assert_)
        ret->assert_ = assert_->Copy();
    if(declare_)
        ret->declare_ = declare_->Copy();
    if(func_call_)
        ret->func_call_ = func_call_->Copy();
    ret->cmd_struct_ = cmd_struct_;
    return ret;
}

//CCmdStruct
CCmdStruct::CCmdStruct(int ln)
    : lineno_(ln)
    , endlineno_(0)
    , cmd_send_flag_(0)
    , inds_(recv_data_)
{}

std::string CCmdStruct::ToString() const{
    std::ostringstream oss;
    oss<<"(struct_name_="<<struct_name_
        <<",cmd_send_flag_="<<cmd_send_flag_
        <<")";
    return oss.str();
}

std::string CCmdStruct::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")"<<struct_name_;
    return oss.str();
}

CSharedPtr<CCmdStruct> CCmdStruct::StructCopy() const
{
    CSharedPtr<CCmdStruct> ret = New<CCmdStruct>(lineno_);
    ret->endlineno_ = endlineno_;
    //cmd_send_flag_
    ret->struct_name_ = struct_name_;
    //var_table
    for(size_t i = 0;i < stmt_list_.size();++i)
        ret->stmt_list_.push_back(stmt_list_[i]->Copy());
    return ret;
}

void CCmdStruct::SetByteOrder(bool net_bo)
{
    assert(IsCmd());
    if(IsSend())
        outds_.OrderType(net_bo);
    else if(IsRecv())
        inds_.OrderType(net_bo);
    else{
        assert(0);
    }
}

void CCmdStruct::AddConnection(CSharedPtr<CValue> conn,int lineno)
{
    assert(IsCmd());
    assert(conn && conn->IsConnection());
    if(!conn_list_.empty()){
        RUNTIME_ERR(lineno,"only one connction is supported for one command");
    }else
        conn_list_.push_back(conn);
}

bool CCmdStruct::PutValue(CSharedPtr<CValue> v)
{
    assert(IsCmd());
    assert(v);
    return (outds_<<*v);
}

bool CCmdStruct::PostPutValue(CSharedPtr<CValue> v,size_t offset)
{
    assert(IsCmd());
    assert(v);
    return (outds_<<Manip::offset_value(offset,*v));
}

bool CCmdStruct::PostInsertValue(CSharedPtr<CValue> v,size_t offset)
{
    assert(IsCmd());
    assert(v);
    return (outds_<<Manip::insert(offset,*v));
}

void CCmdStruct::Begin(CSharedPtr<CExpr> v)
{
    assert(IsCmd());
    assert(v);
    if(!begin_list_)
        begin_list_ = New<CArgList>(lineno_);
    begin_list_->Add(v);
}

void CCmdStruct::End(CSharedPtr<CExpr> v)
{
    assert(IsCmd());
    assert(begin_list_ && v);
    begin_list_->Erase(v);
}

bool CCmdStruct::SendData(const std::vector<char> & buf) const
{
    assert(IsCmd());
    for(std::vector<CSharedPtr<CValue> >::const_iterator i = conn_list_.begin();
        i != conn_list_.end();++i)
    {
        assert(*i);
        const CValue & v = **i;
        assert(v.IsConnection());
        if(v.type_ == 12){  //tcp
            assert(v.tcp_);
            ssize_t n = v.tcp_->SendData(buf,v.tcp_->timeMs_);
            if(n < 0){
                RUNTIME_ERR(endlineno_,"send tcp data to "<<v.tcp_->ToString()
                    <<" error,"<<CSocket::ErrMsg());
                return false;
            }
        }else{              //udp
            assert(v.udp_);
            ssize_t n = v.udp_->SendData(buf);
            if(n < 0){
                RUNTIME_ERR(endlineno_,"send udp data to "<<v.udp_->ToString()
                    <<" error,"<<CSocket::ErrMsg());
                return false;
            }
        }
    }
    return true;
}

bool CCmdStruct::GetValue(CSharedPtr<CValue> v,int lineno)
{
    assert(IsCmd());
    assert(v);
    assert(!v->IsRaw());
    return GetVal(*v,lineno);
}

bool CCmdStruct::GetRaw(std::string & res,const std::string & v,int lineno)
{
    assert(IsCmd());
    for(size_t i = 0;i < v.length();++i){
        char ch = 0;
        if(!GetVal(ch,lineno)){
            RUNTIME_ERR(lineno,"recv RAW string error");
            return false;
        }
        res.push_back(ch);
        if(ch != v[i])
            return false;
    }
    return true;
}

bool CCmdStruct::GetArray(CSharedPtr<CDeclare> d)
{
    assert(IsCmd());
    const U32 MAX_ARRAY_SIZE = 65535;
    assert(d && d->IsArray());
    if(!d->var_->array_type_->HasSize()){
        U32 sz = 0;
        if(!GetVal(sz,d->lineno_)){
            RUNTIME_ERR(d->lineno_,"recv array size error");
            return false;
        }else if(sz > MAX_ARRAY_SIZE){
            RUNTIME_ERR(d->lineno_,"array size is larger than "<<MAX_ARRAY_SIZE);
            return false;
        }else
            d->var_->array_type_->sz_ = int(sz);
    }
    assert(d->val_);
    SHOW(CRuntime::RealVarname(d->var_->varname_)<<".size() = "
        <<d->var_->array_type_->sz_);
    for(int i = 0;i < d->var_->array_type_->sz_;++i){
        if(GetVal(*d->val_,d->lineno_)){
            SHOW(CRuntime::RealVarname(d->var_->varname_)<<"["<<i<<"] = "
                <<d->val_->ShowValue());
        }else{
            RUNTIME_ERR(d->lineno_,"recv '"<<d->var_->varname_<<"["<<i
                <<"]' error");
            return false;
        }
    }
    return true;
}

bool CCmdStruct::GetAssert(CSharedPtr<CDeclare> d,CSharedPtr<CValue> v)
{
    assert(IsCmd());
    assert(d && d->IsAssert());
    assert(d->val_);
    if(d->val_->IsRaw()){
        assert(v->IsString());
        bool ret = GetRaw(d->val_->str_,v->str_,d->lineno_);
        SHOW(CRuntime::RealVarname(d->var_->varname_)<<" = "<<d->val_->ShowValue());
        return ret;
    }else{
        if(!GetVal(*d->val_,d->lineno_)){
            RUNTIME_ERR(d->lineno_,"recv '"<<d->var_->varname_<<"' error");
            return false;
        }
        SHOW(CRuntime::RealVarname(d->var_->varname_)<<" = "<<d->val_->ShowValue());
        assert(v);
        switch(FunAssert(d->op_token_,d->val_,v)){
            case 1:return true;
            case 0:break;
            case -1:{
                RUNTIME_ERR(lineno_,"prediction between signed and unsigned integers");
                break;}
            case -2:{
                GAMMAR_ERR(lineno_,"invalid argument type for prediction");
                break;}
            case -3:{
                GAMMAR_ERR(lineno_,"invalid operator type for prediction");
                break;}
        }
    }
    return false;
}

bool CCmdStruct::GetStreamIn(CSharedPtr<CDeclare> d,CSharedPtr<CValue> v)
{
    assert(IsCmd());
    assert(d && d->IsStreamIn());
    assert(d->val_);
    if(!d->val_->IsString()){
        GAMMAR_ERR(lineno_,"expect string type as left hand argument for stream-in operator");
        return false;
    }
    assert(v);
    if(!v->IsInteger()){
        GAMMAR_ERR(lineno_,"expect integer type as right hand argument for stream-in operator");
        return false;
    }
    U64 i = 0;
    for(int j = 0;j < 20;++j){  //log10(2^64) == 19.3
        char ch = 0;
        if(!GetVal(ch,d->lineno_)){
            RUNTIME_ERR(lineno_,"recv '"<<d->var_->varname_<<"' error");
            return false;
        }
        if(ch >= '0' && ch <= '9'){
            i = i * 10 + ch - '0';
            d->val_->str_.push_back(ch);
        }else{  //put back one char
            inds_>>Manip::skip(-1);
            break;
        }
    }
    if(!v->FromInteger(i)){
        RUNTIME_ERR(lineno_,"value '"<<i<<"' is too large for right hand argument");
        return false;
    }
    return true;
}

bool CCmdStruct::RecvData(int lineno)
{
    assert(IsCmd());
    const size_t MAX_BUF = 32 << 10;    //32k
    assert(!conn_list_.empty() && conn_list_[0]);
    const CValue & v = *conn_list_[0];
    assert(v.IsConnection());
    const size_t off = inds_.Tell();
    if(v.type_ == 12){  //tcp
        assert(v.tcp_);
        ssize_t n = v.tcp_->RecvData(recv_data_,MAX_BUF);
        if(n < 0){
            RUNTIME_ERR(lineno,"recv data error,"<<CSocket::ErrMsg());
            return false;
        }else if(n == 0){
            RUNTIME_ERR(lineno,"remote peer close,"<<CSocket::ErrMsg());
            return false;
        }
        inds_.SetSource(&recv_data_[0],recv_data_.size(),runtime().net_byte_order_);
        inds_>>Manip::skip(off);
    }else{              //udp
        assert(v.udp_);
        if(!recv_data_.empty())
            return false;
        ssize_t n = v.udp_->RecvData(recv_data_,MAX_BUF);
        if(n < 0){
            RUNTIME_ERR(lineno,"recv data error,"<<CSocket::ErrMsg());
            return false;
        }else if(n == 0){
            RUNTIME_ERR(lineno,"remote peer close,"<<CSocket::ErrMsg());
            return false;
        }
        inds_.SetSource(&recv_data_[0],recv_data_.size(),runtime().net_byte_order_);
        inds_>>Manip::skip(off);

    }
    return true;
}

void CCmdStruct::DumpRecvData() const
{
    assert(IsCmd());
    SHOW("  RECV data =");
    if(!recv_data_.empty()){
        SHOW(DumpFormat(recv_data_));
    }
}

bool CCmdStruct::EnsureRecvData(size_t sz,int lineno)
{
    assert(IsCmd());
    if(!sz)
        return true;
    const size_t cur = inds_.Tell();
    while(sz + cur > recv_data_.size())
        if(!RecvData(lineno))
            return false;
    inds_.SetSource(&recv_data_[0],recv_data_.size(),runtime().net_byte_order_);
    inds_>>Manip::skip(cur);
    return true;
}

void CCmdStruct::InvokeFun(bool (*fp)(std::vector<char> &,std::vector<char> &),size_t sz,int lineno,const std::string & fname)
{
    assert(IsCmd());
    assert(fp);
    SHOW("  before invoke function '"<<fname<<"' data = ");
    if(IsSend()){
        std::vector<char> src;
        outds_.ExportData(src);
        SHOW(DumpFormat(src));
        std::vector<char> dst;
        if(!fp(src,dst)){
            RUNTIME_ERR(lineno,"invoke function '"<<fname<<"' returns false");
            dst.swap(src);
        }
        outds_.ImportData(dst);
    }else if(IsRecv()){     //recv
        SHOW(DumpFormat(recv_data_));
        if(!EnsureRecvData(sz,lineno))
            return;
        const size_t cur = inds_.Tell();
        std::vector<char> dst;
        if(fp(recv_data_,dst)){
            recv_data_.swap(dst);
        }else{
            RUNTIME_ERR(lineno,"invoke function '"<<fname<<"' returns false");
        }
        if(cur > recv_data_.size()){
            RUNTIME_ERR(lineno,"not enough data left after function '"<<fname
                <<"' called");
            return;
        }
        inds_.SetSource(&recv_data_[0],recv_data_.size(),runtime().net_byte_order_);
        inds_>>Manip::skip(cur);
    }
}
