#include "global.h"
#include "dbg.h"
#include "tokens.h"

//CFixValue
CFixValue::CFixValue(int ln)
    : lineno_(ln)
    , type_(DT_NONE)
    , i64_(0)
{}

std::string CFixValue::ToString() const{
    std::ostringstream oss;
    oss<<"(type_="<<type_;
    switch(type_){
        case DT_INT:oss<<",int_="<<int_;break;
        case DT_LONG:oss<<",long_="<<long_;break;
        case DT_I64:oss<<",i64_="<<i64_;break;
        case DT_STR:oss<<",strIdx_="<<strIdx_;break;
        case DT_PA:oss<<",prog_arg_=@"<<prog_arg_;break;
    }
    oss<<")";
    return oss.str();
}

std::string CFixValue::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")";
    return oss.str();
}

CSharedPtr<CValue> CFixValue::Evaluate(int lineno) const
{
    CSharedPtr<CValue> ret = New<CValue>();
    ret->type_ = type_;
    switch(type_){
        case DT_INT:
            ret->int_ = int_;
            break;
        case DT_LONG:
            ret->long_ = long_;
            break;
        case DT_I64:
            ret->s64_ = i64_;
            break;
        case DT_STR:
            ret->str_ = program().GetQstr(strIdx_);
            break;
        case DT_PA:{
            const char * const pa = PM_ARG(prog_arg_);
            if(!pa){
                RUNTIME_ERR(lineno,"expect PROGRAM ARGUMENT '$"<<prog_arg_<<"'");
                return 0;
            }
            ret->str_ = pa;
            break;}
        default:
            GAMMAR_ERR(lineno,"invalid fixed value type="<<type_<<"(internal error)");
            return 0;
    }
    return ret;
}

//CVariable
CVariable::CVariable(int ln)
    : lineno_(ln)
    , tp_token_(0)
    , ref_count_(0)
    , begin_(STATUS_BEGIN_READY)
{}

std::string CVariable::ToString() const{
    std::ostringstream oss;
    oss<<"(varname_="<<varname_
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
        GAMMAR_ERR(lineno,"cannot evaluate array, see LINE "<<lineno_);
        return 0;
    }
    CSharedPtr<CDeclare> decl = runtime().FindVar(varname_);
    if(!decl){
        GAMMAR_ERR(lineno,"variable '"<<CRuntime::RealVarname(varname_)
            <<"' not found(internal error)");
        return 0;
    }
    if(!decl->val_){
        GAMMAR_ERR(lineno,"variable '"<<CRuntime::RealVarname(varname_)
            <<"' not initialized yet");
        return 0;
    }
    return decl->val_;
}

CSharedPtr<CValue> CVariable::Initial(int lineno) const
{
    if(array_type_)
        return array_type_->Evaluate();
    std::vector<CSharedPtr<CValue> > args;
    return FunEvaluate(tp_token_,args,lineno);
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
        GAMMAR_ERR(lineno,"undefined symbol '"<<CRuntime::RealVarname(var_->varname_)
            <<"'");
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
            GAMMAR_ERR(lineno,"cannot evaluate parameter "<<(i + 1));
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
    , has_sz_(false)
    , sz_(-1)
{}

std::string CArrayType::ToString() const{
    std::ostringstream oss;
    oss<<"(tp_token_="<<tp_token_
        <<",has_sz_="<<has_sz_
        <<",sz_="<<sz_
        <<",sz_expr_="<<signa(sz_expr_)
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
    if(sz_expr_ && !DT_IsInteger(sz_expr_->RetType())){
        GAMMAR_ERR(lineno_,"invalid type for array size");
        return false;
    }
    return true;
}

bool CArrayType::CheckDefined(int lineno) const
{
    if(sz_expr_)
        return sz_expr_->CheckDefined(lineno);
    return true;
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
    int type2 = DT_VOID;
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
        case RET_TRUE:return true;
        case RET_SIGN_MISMATCH:{
            RUNTIME_ERR(lineno_,"prediction between signed and unsigned integers");
            break;}
        case RET_TYPE_ERROR:{
            RUNTIME_ERR(lineno_,"invalid argument type for prediction");
            break;}
        case RET_OP_ERROR:{
            RUNTIME_ERR(lineno_,"invalid operator type for prediction");
            break;}
    }
    return false;
}

//CDeclare
CDeclare::CDeclare(int ln)
    : lineno_(ln)
    , type_(0)
    , is_def_(0)
    , op_token_(0)
    , eva_priority_(0)
    , offset_(-1)
    , post_byte_order_(true)
{}

std::string CDeclare::ToString() const{
    std::ostringstream oss;
    oss<<"(type_="<<type_
        <<",is_def_="<<is_def_
        <<",var_="<<signa(var_)
        <<",op_token_="<<op_token_
        <<",expr_="<<signa(expr_)
        <<",arglist_="<<signa(arglist_)
        <<",eva_priority_="<<eva_priority_
        <<",val_="<<signa(val_)
        <<",vals_.size()="<<vals_.size()
        <<",offset_="<<offset_
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

bool CDeclare::CheckDefined(CSharedPtr<CCmd> cur_cmd)
{
    bool ret = true;
    CSharedPtr<CVariable> & shadow = var_->shadow_;
    if(shadow){
        --shadow->ref_count_;
        if(cur_cmd == shadow->host_cmd_){
            GAMMAR_ERR(lineno_,"redefine symbol '"<<CRuntime::RealVarname(var_->varname_)
                <<"', see LINE "<<shadow->lineno_);
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
        RUNTIME_ERR(lineno_,"cannot evaluate '"<<CRuntime::RealVarname(var_->varname_)
            <<"'");
    }else
        FixRaw();   //区分STR和RAW类型
    return val_;
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
    std::vector<int> retTypes;
    if(arg_list_)
        arg_list_->RetType(retTypes);
    size_t i = FunArgCheck(ft_token_,retTypes,arg_list_);
    if(i){
        GAMMAR_ERR(lineno_,"argument "<<i<<" type mismatch or missing");
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

int CFuncCall::IsArrayBeginEnd() const
{
    return IsArrayBeginEndToken(ft_token_);
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
    if(global().err_count_)
        throw 0;
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

//CArrayRange
CArrayRange::CArrayRange(int ln)
    : lineno_(ln)
    , start_index_(-1)
    , end_index_(-1)
    , cur_(0)
    , sz_(-1)
{}

//CCmd
CCmd::CCmd(int ln)
    : lineno_(ln)
    , endlineno_(0)
    , send_flag_(0)
    , cur_stmt_index_(0)
    , array_index_(0)
    , inds_(recv_data_)
{}

std::string CCmd::ToString() const{
    std::ostringstream oss;
    oss<<"(cmd_name_="<<cmd_name_
        <<",send_flag_="<<send_flag_
        <<")";
    return oss.str();
}

std::string CCmd::Signature() const{
    std::ostringstream oss;
    oss<<"(LINE:"<<lineno_<<")"<<cmd_name_;
    return oss.str();
}

void CCmd::SetByteOrder(bool net_bo)
{
    if(IsSend())
        outds_.OrderType(net_bo);
    else if(IsRecv())
        inds_.OrderType(net_bo);
    else{
        assert(0);
    }
}

void CCmd::AddConnection(CSharedPtr<CValue> conn,int lineno)
{
    assert(conn && conn->IsConnection());
    if(!conn_list_.empty()){
        RUNTIME_ERR(lineno,"only one SEND/RECV is supported for each CMD");
    }else
        conn_list_.push_back(conn);
}

bool CCmd::PutValue(CSharedPtr<CValue> v)
{
    assert(v);
    return (outds_<<*v);
}

bool CCmd::PutArray(CSharedPtr<CDeclare> d)
{
    assert(d && d->var_->array_type_->sz_ >= 0);
    if(!d->var_->array_type_->has_sz_)
        outds_<<d->var_->array_type_->sz_;
    DBG_RT("d->vals_.size()="<<d->vals_.size());
    if(!d->vals_.empty()){
        for(size_t i = 0;i < d->vals_.size();++i){
            DBG_RT("d->vals_["<<i<<"]="<<to_str(d->vals_[i]));
            if(!(outds_<<*d->vals_[i])){
                DBG_RT("outds_.Status()="<<outds_.Status());
                return false;
            }
        }
    }else if(d->val_){  // char array
        assert(d->val_->IsStrOrPA());
        outds_<<Manip::raw(d->val_->str_.c_str(),d->val_->str_.length());
    }else{
        CSharedPtr<CValue> v = d->var_->Initial(d->lineno_);
        if(!v)
            return false;
        for(int i = 0;i < d->var_->array_type_->sz_;++i)
            if(!(outds_<<*v))
                return false;
    }
    return true;
}

bool CCmd::PostPutValue(CSharedPtr<CValue> v,size_t offset)
{
    assert(v);
    return (outds_<<Manip::offset_value(offset,*v));
}

bool CCmd::PostInsertValue(CSharedPtr<CValue> v,size_t offset)
{
    assert(v);
    return (outds_<<Manip::insert(offset,*v));
}

void CCmd::Begin(CSharedPtr<CExpr> v)
{
    assert(v);
    if(!begin_list_)
        begin_list_ = New<CArgList>(lineno_);
    begin_list_->Add(v);
}

void CCmd::End(CSharedPtr<CExpr> v)
{
    assert(begin_list_ && v);
    begin_list_->Erase(v);
}

bool CCmd::BeginEmpty() const
{
    return (!begin_list_ || begin_list_->args_.empty());
}

bool CCmd::SendData(const std::vector<char> & buf) const
{
    for(std::vector<CSharedPtr<CValue> >::const_iterator i = conn_list_.begin();
        i != conn_list_.end();++i)
    {
        assert(*i);
        const CValue & v = **i;
        assert(v.IsConnection());
        if(v.type_ == DT_TCP){  //tcp
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

bool CCmd::GetValue(CSharedPtr<CValue> v,int lineno)
{
    assert(v);
    assert(!v->IsRaw());
    return GetVal(*v,lineno);
}

bool CCmd::GetRaw(std::string & res,const std::string & v,int lineno)
{
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

bool CCmd::GetArray(CSharedPtr<CDeclare> d)
{
    assert(d && d->IsArray());
    U32 sz = 0;
    if(!d->var_->array_type_->HasSize()){
        if(!GetVal(sz,d->lineno_)){
            RUNTIME_ERR(d->lineno_,"recv array size error");
            return false;
        }else if(sz > MAX_ARRAY_SIZE){
            ASSERT_FAIL(this,d->lineno_,"array size is larger than "<<MAX_ARRAY_SIZE);
        }else
            d->var_->array_type_->sz_ = int(sz);
    }else
        sz = d->var_->array_type_->sz_;
    if(!d->val_)
        d->val_ = d->var_->Initial(d->lineno_);
    SHOW(CRuntime::RealVarname(d->var_->varname_)<<ArrayIndexString()
        <<".size() = "<<sz);
    d->vals_.resize(sz);
    for(U32 i = 0;i < sz;++i){
        if(GetVal(*d->val_,d->lineno_)){
            SHOW(CRuntime::RealVarname(d->var_->varname_)<<ArrayIndexString()<<"["<<i<<"] = "
                <<d->val_->ShowValue());
        }else{
            RUNTIME_ERR(d->lineno_,"recv '"<<CRuntime::RealVarname(d->var_->varname_)<<"["<<i
                <<"/"<<d->var_->array_type_->sz_<<"]' error");
            return false;
        }
    }
    return true;
}

bool CCmd::GetAssert(CSharedPtr<CDeclare> d,CSharedPtr<CValue> v)
{
    assert(d && d->IsAssert());
    assert(d->val_);
    if(d->val_->IsRaw()){
        assert(v->IsString());
        bool ret = GetRaw(d->val_->str_,v->str_,d->lineno_);
        SHOW(CRuntime::RealVarname(d->var_->varname_)<<ArrayIndexString()
            <<" = "<<d->val_->ShowValue());
        return ret;
    }else{
        if(!GetVal(*d->val_,d->lineno_)){
            RUNTIME_ERR(d->lineno_,"recv '"<<CRuntime::RealVarname(d->var_->varname_)
                <<"' error");
            return false;
        }
        SHOW(CRuntime::RealVarname(d->var_->varname_)<<ArrayIndexString()
            <<" = "<<d->val_->ShowValue());
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

bool CCmd::GetStreamIn(CSharedPtr<CDeclare> d,CSharedPtr<CValue> v)
{
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
            RUNTIME_ERR(lineno_,"recv '"<<CRuntime::RealVarname(d->var_->varname_)
                <<"' error");
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

bool CCmd::RecvData(int lineno)
{
    const size_t MAX_BUF = 32 << 10;    //32k
    assert(!conn_list_.empty() && conn_list_[0]);
    const CValue & v = *conn_list_[0];
    assert(v.IsConnection());
    const size_t off = inds_.Tell();
    if(v.type_ == DT_TCP){  //tcp
        assert(v.tcp_);
        ssize_t n = v.tcp_->RecvData(recv_data_,MAX_BUF);
        if(n < 0){
            RUNTIME_ERR(lineno,"recv data error,"<<CSocket::ErrMsg());
            return false;
        }else if(n == 0){
            RUNTIME_ERR(lineno,"remote peer close,"<<CSocket::ErrMsg());
            return false;
        }
        inds_.SetSource(&recv_data_[0],recv_data_.size(),runtime().cur_byte_order_);
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
        inds_.SetSource(&recv_data_[0],recv_data_.size(),runtime().cur_byte_order_);
        inds_>>Manip::skip(off);

    }
    return true;
}

void CCmd::DumpRecvData() const
{
    SHOW("  RECV data =");
    if(!recv_data_.empty()){
        SHOW(DumpFormat(recv_data_));
    }
}

bool CCmd::EnsureRecvData(size_t sz,int lineno)
{
    if(!sz)
        return true;
    const size_t cur = inds_.Tell();
    while(sz + cur > recv_data_.size())
        if(!RecvData(lineno))
            return false;
    inds_.SetSource(&recv_data_[0],recv_data_.size(),runtime().cur_byte_order_);
    inds_>>Manip::skip(cur);
    return true;
}

void CCmd::InvokeFun(__SRC_UserFunc fp,unsigned int dst_max_len,size_t sz,int lineno,const std::string & fname)
{
    assert(fp && dst_max_len);
    if(runtime().Debug()){
        SHOW("  before invoke function '"<<fname<<"' data = ");
    }
    if(IsSend()){
        std::vector<char> src;
        outds_.ExportData(src);
        if(runtime().Debug()){
            SHOW(DumpFormat(src));
        }
        std::vector<char> dst(dst_max_len);
        if(!fp(&src[0],(unsigned int)src.size(),&dst[0],dst_max_len)){
            RUNTIME_ERR(lineno,"invoke function '"<<fname<<"' returns false");
            dst.swap(src);
        }
        dst.resize(dst_max_len);
        outds_.ImportData(dst);
    }else if(IsRecv()){     //recv
        if(runtime().Debug()){
            SHOW(DumpFormat(recv_data_));
        }
        if(!EnsureRecvData(sz,lineno))
            return;
        const size_t cur = inds_.Tell();
        std::vector<char> dst(dst_max_len);
        if(fp(&recv_data_[0],(unsigned int)recv_data_.size(),&dst[0],dst_max_len)){
            dst.resize(dst_max_len);
            recv_data_.swap(dst);
        }else{
            RUNTIME_ERR(lineno,"invoke function '"<<fname<<"' returns false");
        }
        if(cur > recv_data_.size()){
            RUNTIME_ERR(lineno,"not enough data left after function '"<<fname
                <<"' called");
            return;
        }
        inds_.SetSource(&recv_data_[0],recv_data_.size(),runtime().cur_byte_order_);
        inds_>>Manip::skip(cur);
    }
}

void CCmd::AddArrayBegin(int lineno)
{
    array_stack_.push_back(array_range_.size());
    array_range_.push_back(CArrayRange(lineno));
    array_range_.back().start_index_ = stmt_list_.size();
}

void CCmd::AddArrayEnd(int lineno)
{
    if(array_stack_.empty()){
        RUNTIME_ERR(lineno,"cannot END ARRAY without BEGIN ARRAY");
        return;
    }
    array_range_[array_stack_.back()].end_index_ = stmt_list_.size();
    array_stack_.pop_back();
}

void CCmd::StartArray(int lineno)
{
    if(!IsRecv()){
        RUNTIME_ERR(lineno,"ARRAY size is unknown");
        return;
    }
    U32 sz = 0;
    if(!GetVal(sz,lineno)){
        RUNTIME_ERR(lineno,"cannot recv array size");
    }else{
        SHOW("  ARRAY_SIZE = "<<sz);
        if(sz >= MAX_ARRAY_SIZE){
            ASSERT_FAIL(this,lineno,"array size is larger than "<<MAX_ARRAY_SIZE);
        }
        StartArray(sz,lineno);
    }
}

void CCmd::StartArray(size_t sz,int lineno)
{
    array_range_[array_index_].sz_ = sz;
    if(!sz){
        cur_stmt_index_ = array_range_[array_index_].end_index_;
    }else{
        --array_range_[array_index_].sz_;
        array_stack_.push_back(array_index_);
    }
    ++array_index_;
}

void CCmd::EndArray(int lineno)
{
    if(array_stack_.empty()){
        RUNTIME_ERR(lineno,"cannot END ARRAY without BEGIN ARRAY");
        return;
    }
    size_t i = array_stack_.back();
    assert(array_range_[i].cur_ <= array_range_[i].sz_);
    if(array_range_[i].cur_ == array_range_[i].sz_){   //array ends
        array_stack_.pop_back();
    }else{                        //array repeats
        assert(array_range_[i].start_index_ >= 0);
        ++array_range_[i].cur_;
        cur_stmt_index_ = array_range_[i].start_index_;
    }
}

std::string CCmd::ArrayIndexString() const
{
    std::ostringstream oss;
    for(size_t i = 0;i < array_stack_.size();++i){
        size_t index = array_stack_[i];
        oss<<"["<<array_range_[index].cur_<<"]";
    }
    return oss.str();
}
