#ifndef DOZERG_REFERENCE_COUNT_POINTER_H_20070828
#define DOZERG_REFERENCE_COUNT_POINTER_H_20070828

#include "impl/SharedPtr_impl.h"

template<class T>
class CSharedPtr
{   //typedefs
    typedef CSharedPtr<T>   __Myt;
    typedef _ref_imp<T>     __ref_type;
public:
    typedef T & reference;
    typedef T * pointer;
private:
    typedef void (__Myt::*safe_bool_type)(pointer);
public:
    //functions
    CSharedPtr(pointer p = 0):ref_(0){init(p);}
    CSharedPtr(const __Myt & a):ref_(0){__ref_type::changeRef(ref_,a.ref_);}
    ~CSharedPtr(){__ref_type::subRef(ref_);}
    __Myt & operator =(const __Myt & a){
        __ref_type::changeRef(ref_,a.ref_);
        return *this;
    }
    __Myt & operator =(pointer a){
        if(operator !=(a)){
            __ref_type::subRef(ref_);
            init(a);
        }
        return *this;
    }
    reference operator *() const{return *ref_->ptr_;}
    pointer operator ->() const{return ref_->ptr_;}
    bool operator !() const{return !ref_;}
    operator safe_bool_type() const{return operator !() ? 0 : &__Myt::init;}
    bool operator ==(const __Myt & a) const{return ref_ == a.ref_;}
    bool operator !=(const __Myt & a) const{return !operator ==(a);}
    bool operator ==(pointer a) const{
        return operator !() ? !a : a == operator ->();
    }
    bool operator !=(pointer a) const{return !operator ==(a);}
private:
    void init(pointer p){
        if(p)
            ref_ = New<__ref_type>(p);
    }
    //field
    __ref_type * ref_;
};

#endif
