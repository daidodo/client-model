#ifndef DOZERG_REFERENCE_COUNT_POINTER_IMPL_H_20080226
#define DOZERG_REFERENCE_COUNT_POINTER_IMPL_H_20080226

#include "mm.h"

template<class Elem>
struct _ref_imp{
    explicit _ref_imp(Elem * pe)
        : ptr_(pe)
        , cnt_(1)
    {}
    void addRef(_ref_imp *& p){
        p = this;
        ++cnt_;
    }
    static void changeRef(_ref_imp *& p,_ref_imp * v){
        if(p != v){
            subRef(p);
            if(v)
                v->addRef(p);
        }
    }
    static void subRef(_ref_imp *& p){
        if(p){
            if(!--(p->cnt_)){
                Delete(p->ptr_);
                Delete(p);
            }
            p = 0;
        }
    }
private:
    _ref_imp(const _ref_imp &);
    _ref_imp & operator =(const _ref_imp &);
public:
    Elem *  ptr_;
private:
    int cnt_;
};

#endif
