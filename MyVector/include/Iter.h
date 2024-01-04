#ifndef ITER
#define ITER
#include <iostream>

namespace MVec {
template <class T>
    class Iter {
    public:
        T* ptr;

        //构造函数
        Iter() : ptr(nullptr) {}
        Iter(T* ptr){
            this->ptr = ptr;
        }

        //一些重载方法
        //重载运算符it++,将it返回给用户，并且it自增1。
        Iter operator ++(int){
            T * old_data = ptr;
            ptr++;
            return Iter(old_data);
        }
        
        //重载运算符++it，将it++返回给用户，并且it自增1。
        Iter& operator ++(){
            ptr++;
            return *this;
        }
        //重载运算符*it，将it返回给用户。
        T& operator *(){
            return *ptr;
        }
        //重载运算符->it，将it返回给用户。
        T* operator ->(){
            return ptr;
        }
        //重载运算符==，返回是否相等，相等-->true,不相等-->false。
        bool operator ==(Iter const &temp){
            return ptr == temp.ptr;
        }
        //重载运算符!=，返回是否不相等，不相等-->true,相等-->false。
        bool operator !=(Iter const &temp){
            return ptr != temp.ptr;
        }
        //重载运算符--it,将it-1t返回给用户，并且it自减1。
        Iter& operator --(){
            ptr--;
            return *this;
        }
        //重载运算符it--,将it返回给用户，并且it自减1。
        Iter operator --(int){
            T * old_data = ptr;
            ptr--;
            return Iter(old_data);
        }
        //重载运算符it+n,将it返回给用户。
        Iter operator +(int n){
            return Iter(ptr + n);
        }
        //重载运算符it-n,将it返回给用户。
        Iter operator -(int n){
            return Iter(ptr - n);
        }


    };
}  // namespace MVec

#endif  // ITER