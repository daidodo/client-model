#ifndef DOZERG_DATA_STREAM_H_20070905
#define DOZERG_DATA_STREAM_H_20070905

#include <cassert>
#include <string>
#include <vector>
#include "impl/DataStream_impl.h"
#include "util.h"

class CInByteStream : public CDataStreamBase
{
    typedef CInByteStream __Myt;
    static const bool DEF_NET_BYTEORDER = true;    //默认使用网络字节序(true)还是本地字节序(false)
    const char *    data_;
    size_t          len_;
    size_t          cur_;
    bool            need_reverse_;  //是否需要改变字节序
public:
    CInByteStream(const char * d,size_t l,bool netByteOrder = DEF_NET_BYTEORDER){   //netByteOrder表示是否按网络字节序
        SetSource(d,l,netByteOrder);
    }
    CInByteStream(const unsigned char * d,size_t l,bool netByteOrder = DEF_NET_BYTEORDER){
        SetSource(d,l,netByteOrder);
    }
    CInByteStream(const signed char * d,size_t l,bool netByteOrder = DEF_NET_BYTEORDER){
        SetSource(d,l,netByteOrder);
    }
    CInByteStream(const std::vector<char> & d,bool netByteOrder = DEF_NET_BYTEORDER){
        SetSource(d,netByteOrder);
    }
    CInByteStream(const std::vector<unsigned char> & d,bool netByteOrder = DEF_NET_BYTEORDER){
        SetSource(d,netByteOrder);
    }
    CInByteStream(const std::vector<signed char> & d,bool netByteOrder = DEF_NET_BYTEORDER){
        SetSource(d,netByteOrder);
    }
    void SetSource(const char * d,size_t l,bool netByteOrder = DEF_NET_BYTEORDER){
        data_ = d;
        len_ = l;
        cur_ = 0;
        need_reverse_ = NeedReverse(netByteOrder);
        ResetStatus();
    }
    void SetSource(const unsigned char * d,size_t l,bool netByteOrder = DEF_NET_BYTEORDER){
        SetSource((const char *)d,l,netByteOrder);
    }
    void SetSource(const signed char * d,size_t l,bool netByteOrder = DEF_NET_BYTEORDER){
        SetSource((const char *)d,l,netByteOrder);
    }
    void SetSource(const std::vector<char> & d,bool netByteOrder = DEF_NET_BYTEORDER){
        SetSource(&d[0],d.size(),netByteOrder);
    }
    void SetSource(const std::vector<unsigned char> & d,bool netByteOrder = DEF_NET_BYTEORDER){
        SetSource((const char *)&d[0],d.size(),netByteOrder);
    }
    void SetSource(const std::vector<signed char> & d,bool netByteOrder = DEF_NET_BYTEORDER){
        SetSource((const char *)&d[0],d.size(),netByteOrder);
    }
    //设置字节序类型
    void OrderType(EOrderType ot){need_reverse_ = NeedReverse(ot);}
    void OrderType(bool netOrder){need_reverse_ = NeedReverse(netOrder);}
    //按照dir指定的方向设置cur_指针偏移
    //返回cur_最后的绝对偏移
    size_t Seek(ssize_t off,ESeekDir dir){
        switch(dir){
            case Begin:
                cur_ = off;
                break;
            case End:
                assert(size_t(off) <= len_);
                cur_ = len_ - off;
                break;
            case Cur:
                cur_ += off;
                break;
            default:
                assert(0);
        }
        return cur_;
    }
    //返回当前cur_指针的偏移，dir表示相对位置
    size_t Tell(ESeekDir dir = Begin) const{
        switch(dir){
            case Begin:
                return cur_;
            case End:
                return (len_ > cur_ ? len_ - cur_ : 0);
            default:;
        }
        return 0;
    }
    size_t CurPos() const{return Tell();}
    //剩余的字节数
    size_t LeftSize() const{return Tell(End);}
    //read PODs
    __Myt & operator >>(char & c)               {return readPod(c);}
    __Myt & operator >>(signed char & c)        {return readPod(c);}
    __Myt & operator >>(unsigned char & c)      {return readPod(c);}
    __Myt & operator >>(short & c)              {return readPod(c);}
    __Myt & operator >>(unsigned short & c)     {return readPod(c);}
    __Myt & operator >>(int & c)                {return readPod(c);}
    __Myt & operator >>(unsigned int & c)       {return readPod(c);}
    __Myt & operator >>(long & c)               {return readPod(c);}
    __Myt & operator >>(unsigned long & c)      {return readPod(c);}
    __Myt & operator >>(long long & c)          {return readPod(c);}
    __Myt & operator >>(unsigned long long & c) {return readPod(c);}
    //read std::string
    __Myt & operator >>(std::string & c){
        U32 sz;
        operator >>(sz);
        if(ensure(sz)){
            c.assign(data_ + cur_ ,data_ + cur_ + sz);
            cur_ += sz;
        }
        return *this;
    }
    //read array( = length + raw array)
    template<class T>
    __Myt & operator >>(T * c){
        U32 sz;
        operator >>(sz);
        return readRaw(c,sz);
    }
    //read array( = length + raw array) through CManipulatorArray
    template<class T>
    __Myt & operator >>(const CManipulatorArray<T> & m){
        U32 sz;
        operator >>(sz);
        if(sz > m.Size1()){
            Status(1);
            return *this;
        }
        m.Size2(sz);
        return readRaw(m.Ptr(),sz);
    }
    //read raw array through CManipulatorRaw
    template<class T>
    __Myt & operator >>(const CManipulatorRaw<T> & m){
        return readRaw(m.Ptr(),m.Size());
    }
    //read range of raw array through CManipulatorRange
    template<class Iter>
    __Myt & operator >>(const CManipulatorRange<Iter> & m){
        for(Iter i = m.Begin();i != m.End();++i)
            if(!(*this>>(*i)))
                break;
        return *this;
    }
    //set order type(NetOrder or HostOrder) through CManipulatorSetOrder
    __Myt & operator >>(const CManipulatorSetOrder & m){
        OrderType(m.Order());
        return *this;
    }
    //set cur_ position through CManipulatorSeek
    __Myt & operator >>(const CManipulatorSeek & m){
        Seek(m.Off(),m.Dir());
        return *this;
    }
    //read value from a particular position but not change cur_
    template<class T>
    __Myt & operator >>(const CManipulatorOffsetValue<T> & m){
        size_t old = cur_;
        Seek(m.Off(),Begin);
        *this>>(m.Value());
        Seek(old,Begin);
        return *this;
    }
private:
    template<typename T>
    __Myt & readPod(T & c){
        if(ensure(sizeof(T))){
            memcpy(&c,data_ + cur_,sizeof(T));
            if(need_reverse_ && sizeof(T) > 1)
                c = SwapByteOrder(c);
            cur_ += sizeof(T);
        }
        return *this;
    }
    template<typename T>
    __Myt & readRaw(T * c,size_t sz){
        assert(c);
        if(!__ManipTypeTraits<T>::CanMemcpy
            || (sizeof(T) > 1 && need_reverse_))
        {
            for(size_t i = 0;i < sz;++i,++c)
                if(!(*this>>(*c)))
                    break;
        }else{
            sz *= sizeof(T);
            if(ensure(sz)){
                memcpy(c,data_ + cur_,sz);
                cur_ += sz;
            }
        }
        return *this;
    }
    template<typename T>
    __Myt & readArray(T * c){
        U32 sz;
        operator >>(sz);
        return readRaw(c,sz);
    }
    bool ensure(size_t sz){     //防止越界访问data_
        if(operator !())
            return false;
        if(len_ < cur_ + sz){
            Status(1);
            return false;
        }
        return true;
    }
};

class COutByteStream : public CDataStreamBase
{
    typedef COutByteStream __Myt;
    static const bool DEF_NET_BYTEORDER = true;    //默认使用网络字节序(true)还是本地字节序(false)
    std::vector<char>   data_;
    size_t              cur_;
    bool                need_reverse_;  //是否需要改变结果的byte order
public:
    explicit COutByteStream(size_t sz = 100,bool netByteOrder = DEF_NET_BYTEORDER)
        : data_(sz)
        , cur_(0)
        , need_reverse_(NeedReverse(netByteOrder))
    {}
    //设置/获取字节序类型
    void OrderType(bool netOrder){need_reverse_ = NeedReverse(netOrder);}
    void OrderType(EOrderType ot){need_reverse_ = NeedReverse(ot);}
    EOrderType OrderType() const{return (need_reverse_ ? HostOrder : NetOrder);}
    //按照dir指定的方向设置cur_指针偏移
    //返回cur_最后的绝对偏移
    //注意：如果cur_变小，相当于抹掉了cur_之后的数据；如果cur_变大了，相当于留出指定的空位
    size_t Seek(ssize_t off,ESeekDir dir){
        switch(dir){
            case Begin:
                assert(off >= 0);
                if(size_t(off) > cur_)
                    ensure(size_t(off) - cur_);
                cur_ = off;
                break;
            case End:
            case Cur:
                if(off > 0)
                    ensure(off);
                else
                    assert(size_t(-off) < cur_);
                cur_ += off;
                break;
            default:
                assert(0);
        }
        return cur_;
    }
    //返回当前cur_指针的绝对偏移
    size_t Tell() const{return cur_;}
    size_t Size() const{return Tell();}
    //导出所有写入的数据
    //bAppend表示是追加到dst已有数据后面，还是覆盖dst原有的数据
    bool ExportData(std::string & dst,bool bAppend = false){
        data_.resize(cur_);
        if(bAppend){    //数据加到dst后面
            dst.insert(dst.end(),data_.begin(),data_.end());
        }else{          //覆盖dst原有数据
            dst.assign(data_.begin(),data_.end());
        }
        cur_ = 0;
        return true;
    }
    bool ExportData(std::vector<char> & dst,bool bAppend = false){
        data_.resize(cur_);
        if(bAppend){    //数据加到dst后面
            dst.insert(dst.end(),data_.begin(),data_.end());
        }else{          //覆盖dst原有数据
            data_.swap(dst);
        }
        cur_ = 0;
        return true;
    }
    bool ExportData(char * dst,size_t & sz){
        if(sz < data_.size())
            return false;
        sz = data_.size();
        if(sz > 0){
            memcpy(dst,&data_[0],sz);
        }
        cur_ = 0;
        return true;
    }
    //这个函数是专为这个项目加入的
    void ImportData(std::vector<char> & src){
        data_.swap(src);
        cur_ = data_.size();
    }
    //write PODs
    __Myt & operator <<(char c)                 {return writePod(c);}
    __Myt & operator <<(signed char c)          {return writePod(c);}
    __Myt & operator <<(unsigned char c)        {return writePod(c);}
    __Myt & operator <<(short c)                {return writePod(c);}
    __Myt & operator <<(unsigned short c)       {return writePod(c);}
    __Myt & operator <<(int c)                  {return writePod(c);}
    __Myt & operator <<(unsigned int c)         {return writePod(c);}
    __Myt & operator <<(long c)                 {return writePod(c);}
    __Myt & operator <<(unsigned long c)        {return writePod(c);}
    __Myt & operator <<(long long c)            {return writePod(c);}
    __Myt & operator <<(unsigned long long c)   {return writePod(c);}
    //write std::string
    __Myt & operator <<(std::string c){
        return writeArray(c.c_str(),c.length());
    }
    //write array( = length + raw array) through CManipulatorArray
    template<class T>
    __Myt & operator <<(const CManipulatorArray<T> & m){
        return writeArray(m.Ptr(),m.Size1());
    }
    //write raw array through CManipulatorRaw
    template<class T>
    __Myt & operator <<(const CManipulatorRaw<T> & m){
        return writeRaw(m.Ptr(),m.Size());
    }
    //write range of raw array through CManipulatorRange
    template<class Iter>
    __Myt & operator <<(const CManipulatorRange<Iter> & m){
        for(Iter i = m.Begin();i != m.End();++i)
            *this<<(*i);
        return *this;
    }
    //set order type(NetOrder, HostOrder) through CManipulatorSetOrder
    __Myt & operator <<(const CManipulatorSetOrder & m){
        OrderType(m.Order());
        return *this;
    }
    //set cur_ position through CManipulatorSeek
    __Myt & operator <<(const CManipulatorSeek & m){
        Seek(m.Off(),m.Dir());
        return *this;
    }
    //write value to a particular position but not change cur_
    template<class T>
    __Myt & operator <<(const CManipulatorOffsetValue<T> & m){
        size_t old = cur_;
        Seek(m.Off(),Begin);
        *this<<(m.Value());
        if(old > cur_)
            Seek(old,Begin);
        return *this;
    }
    //insert value into a particular position and change cur_ relatively
    template<class T>
    __Myt & operator <<(const CManipulatorInsert<T> & m){
        __Myt ds;
        ds.need_reverse_ = need_reverse_;
        if(ds<<m.Value()){
            std::vector<char> tmp;
            ds.ExportData(tmp);
            data_.insert(data_.begin() + m.Off(),tmp.begin(),tmp.end());
            cur_ += tmp.size();
        }
        return *this;
    }
private:
    template<typename T>
    __Myt & writePod(T c){
        ensure(sizeof(T));
        if(need_reverse_ && sizeof(T) > 1)
            c = SwapByteOrder(c);
        memcpy(&data_[cur_],&c,sizeof(T));
        cur_ += sizeof(T);
        return *this;
    }
    template<typename T>
    __Myt & writeRaw(const T * c,size_t sz){
        assert(c);
        if(!__ManipTypeTraits<T>::CanMemcpy
            || (sizeof(T) > 1 && need_reverse_))
        {
            for(size_t i = 0;i < sz;++i,++c)
                *this<<(*c);
        }else{
            sz *= sizeof(T);
            ensure(sz);
            memcpy(&data_[cur_],c,sz);
            cur_ += sz;
        }
        return *this;
    }
    template<typename T>
    __Myt & writeArray(const T * c,size_t sz){
        operator <<(U32(sz));
        if(sz){
            assert(c);
            return writeRaw(c,sz);
        }else
            return *this;
    }
    void ensure(size_t len){
        size_t curLen = data_.size();
        if(curLen < len + cur_)
            data_.resize(curLen + (curLen >> 1) + len);
    }
};

//manipulators' functions:
namespace Manip{
    //write array( = length + raw array)
    template<class T>
    inline CManipulatorArray<T> array(T * c,size_t sz,size_t * real_sz = 0){
        return CManipulatorArray<T>(c,sz,real_sz);
    }

    //read/write raw array
    template<class T>
    inline CManipulatorRaw<T> raw(T * c,size_t sz){
        return CManipulatorRaw<T>(c,sz);
    }

    //read/write range [first,last) of raw array
    template<class Iter>
    inline CManipulatorRange<Iter> range(Iter first,Iter last){
        return CManipulatorRange<Iter>(first,last);
    }

    //set byte order type(NetOrder or HostOrder)
    inline CManipulatorSetOrder set_order(CDataStreamBase::EOrderType order){
        return CManipulatorSetOrder(order);
    }

    inline CManipulatorSetOrder set_order(bool netByteOrder){
        return CManipulatorSetOrder(
            netByteOrder ? CDataStreamBase::NetOrder : CDataStreamBase::HostOrder);
    }

    //set read/write position
    inline CManipulatorSeek seek(ssize_t off,CDataStreamBase::ESeekDir dir = CDataStreamBase::Begin){
        return CManipulatorSeek(off,dir);
    }

    //skip/reserve certain bytes
    inline CManipulatorSeek skip(ssize_t off){
        return CManipulatorSeek(off,CDataStreamBase::Cur);
    }

    //read/write value from offset position
    template<class T>
    inline CManipulatorOffsetValue<T> offset_value(size_t offset,T & val){
        return CManipulatorOffsetValue<T>(offset,val);
    }
    template<class T>
    inline CManipulatorOffsetValue<const T> offset_value(size_t offset,const T & val){
        return CManipulatorOffsetValue<const T>(offset,val);
    }

    //insert value into offset position
    template<class T>
    inline CManipulatorInsert<T> insert(size_t offset,const T & val){
        return CManipulatorInsert<T>(offset,val);
    }

}//namespace Manip

#endif
