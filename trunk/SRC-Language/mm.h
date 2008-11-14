#ifndef DOZERG_MEMORY_MANAGMENT_H_20081111
#define DOZERG_MEMORY_MANAGMENT_H_20081111

template<class T>
T * New(int ln){
    return new T(ln);
}

template<class T>
void Delete(T *& p){
    typedef char __dummy[sizeof(T)];
    if(p){
        delete p;
        p = 0;
    }
}


#endif