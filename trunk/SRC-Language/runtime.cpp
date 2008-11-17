#include <cassert>
#include "errors.h"
#include "runtime.h"

CRuntime::CRuntime()
    : default_tcp_(true)
{}

bool CRuntime::Interpret(CProgram & program)
{
    for(__StmtList::iterator i = program.global_stmts.begin();
        i != program.global_stmts.end();++i)
    {
        assert(*i);
        processStmt(**i);
    }
    return true;
}

CSharedPtr<CDeclare> CRuntime::FindVar(const std::string & vname)
{
    std::map<std::string,CSharedPtr<CDeclare> >::const_iterator wh = var_table_.find(vname);
    return (wh == var_table_.end() ? 0 : wh->second);
}

void CRuntime::processStmt(CStmt & stmt)
{
    switch(stmt.type_){
        case 1:
            GAMMAR_ERR(stmt.lineno_,"invalid assertion in global scope");
            break;
        case 2:
            assert(stmt.declare_);
            processDeclare(*stmt.declare_);
            break;
        case 3:
            assert(stmt.func_call_);
            processFunc(*stmt.func_call_);
            break;
        case 4:
            assert(stmt.cmd_);
            processCmd(*stmt.cmd_);
            break;
        default:
            GAMMAR_ERR(stmt.lineno_,"(internal error)invalid statement type("
                <<stmt.type_<<")");
    }
}

void CRuntime::processDeclare(CDeclare & decl)
{
    switch(decl.type_){
        case 1:                 //array
            GAMMAR_ERR(decl.lineno_,"invalid array in global scope");
            break;
        case 2:case 3:case 4:   //post
            processPost(decl);
            break;
        case 5:case 6:          //fixed
            processFixed(decl);
            break;
        case 7:
            GAMMAR_ERR(decl.lineno_,"invalid assertion in global scope");
            break;
        case 8:case 9:
            GAMMAR_ERR(decl.lineno_,"invalid stream in global scope");
            break;
        default:
            GAMMAR_ERR(decl.lineno_,"(internal error)invalid declare type("
                <<decl.type_<<")");
    }
}

void CRuntime::processFunc(CFuncCall & func)
{
}

void CRuntime::processCmd(CCmd & cmd)
{
}

void CRuntime::processPost(CDeclare & decl)
{

}

void CRuntime::processFixed(CDeclare & decl)
{
    decl.val_ = decl.expr_->Evaluate();
    if(!decl.val_){
        GAMMAR_ERR(decl.lineno_,"cannot evaluate '"<<decl.var_->varname_
            <<"'");
    }
}
