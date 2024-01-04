#ifndef VEC 
#define VEC

#include<iostream>
#include<initializer_list>
#include<exception>
#include"Iter.h"
#define INITCAP  10000
#define ADDSIZE  1000

namespace MVec
{
    template <class T>
    class Vec{
    private:
        T* data=nullptr;        //存储数据  
        size_t size=0;          //数据大小
        size_t cap=0;           //容器最大容量

    private:
        //迭代器
        class Vec_Iter: public Iter<T>{
            using Iter<T>::Iter;
        };

    protected:
        //给data重新分配空间，并将原数据复制
        void alloc(size_t new_cap){
            //异常处理
            try{
                if(new_cap<=0){
                    throw std::invalid_argument("cap must be positive");
                }
                T* new_data = new T[new_cap];
                //CopyData(this->data, new_data, this->size);
                //这里原本使用的是最简单的复制，但是效率太低，发现使用移动语义会非常快
                std::move(this->data, this->data+this->size, new_data);
                delete[] this->data;
                this->data = new_data;
            } catch(std::bad_alloc& e){
                std::cout<<"bad_alloc: "<<e.what()<<std::endl;
                exit(1);
            } catch(std::invalid_argument& e){
                std::cout<<"invalid_argument: "<<e.what()<<std::endl;
                exit(1);
            }
        }

        //复制函数：从from复制到to，复制size个元素
        void CopyData(T*from, T*to, size_t size){
            for(int i=0; i<size; i++){
                to[i] = from[i];
            }
        }
        // void CopyData(Vec_Iter from_end, Vec_Iter to_end, Vec_Iter final_iter){
        //     while(from_end!=final_iter){
        //         *(to_end--) = *(from_end--);
        //     }
        //     *(to_end) = *(from_end);
        // }

    public:
        //-------------------------------------------构造函数
        //构造空实例
        Vec(){
            alloc(INITCAP+1);
            this->size = 0;
            this->cap = INITCAP;
        }

        //构造具有自定义初始容量的实例
        Vec(size_t size){
            alloc(size+1);
            this->size = 0;
            this->cap = size;
        }
        //拷贝构造
        Vec(const Vec& V){
            size_t new_cap = V.get_cap();
            alloc(new_cap);
            CopyData(V.data, this->data, V.size);
            size = V.size;
            cap = V.cap;
        }
        //new出来的指针数组初始化
        Vec(T*arr, size_t size){
            size_t new_cap = size>INITCAP?size+ADDSIZE:INITCAP;
            this->data = new T[new_cap+1];
            CopyData(arr, this->data, size);
            this->size = size;
            this->cap = new_cap;

        }
        // 形如vector<int> v(10,1); 即创建10个1的vector
        Vec(size_t size, T value){
            size_t new_cap = size>INITCAP?size+ADDSIZE:INITCAP;
            this->data = new T[new_cap+1];
            for(int i=0; i<size; i++){
                this->data[i] = value;
            }
            this->size = size;
            this->cap = new_cap;

        }
        // 形如 vector<int> v = {1,2,3,4,5};
        Vec(std::initializer_list<T> list){
            size_t new_cap = list.size()>INITCAP?list.size()+ADDSIZE:INITCAP;
            this->data = new T[new_cap+1];
            int i=0;
            for(auto it=list.begin(); it!=list.end(); it++){
                this->data[i++] = *it;
            }
            this->size = list.size();
            this->cap = new_cap;
        }

        //移动构造
        Vec(Vec&& V){
            this->data = V.data;
            this->size = V.size;
            this->cap = V.cap;
            V.data = nullptr;
            V.size = 0;
            V.cap = 0;
        }
        // 重载赋值，等价于拷贝构造
        Vec &operator =(const Vec& V){
            if(this==&V){
                return *this;
            }
            size_t new_cap = V.get_cap();
            alloc(new_cap);
            CopyData(V.data, this->data, V.size);
            size = V.size;
            cap = V.cap;
            return *this;
        }

        //----------------------------------------析构函数
        ~Vec(){
            if(data){
                delete[] data;
                data = nullptr;
            }
            size = 0;
            cap = 0;
        }

        //---------------------------------------访问数据内容及容器状态
        //返回容器容量
        size_t get_cap() const{
            return this->cap;
        }
        //返回容器大小
        size_t get_size() const{
            return this->size;
        }
        //展示所有数据
        void show_vec() const{
            for(int i=0; i<this->size; i++){
                std::cout<<this->data[i]<<" ";
            }
            std::cout<<std::endl;
            std::cout<<"size: "<<this->size<<std::endl;
            std::cout<<"cap: "<<this->cap<<std::endl;
        }

        //索引访问值
        T &operator [](size_t index){
            if(index>=this->size){
                throw "index out of range";
            }
            return this->data[index];
        }


        //是否为空
        bool is_empty() const{
            return this->size==0;
        }

        //展示第一个元素
        T front() const{
            return this->data[0];
        }

        //展示最后一个元素
        T back() const{
            return this->data[this->size-1];
        }


        //--------------------------------------增删查改操作
        //push_bcak
        void push_back(T value){
            if(this->size+1>=this->cap){
                alloc(this->cap+ADDSIZE);
                this->cap += ADDSIZE;
            }
                this->data[this->size++] = value;
            return;
        }  

        //pop_back
        void pop_back(){
            if(this->size>0){
                this->size--;
            }
            return;
        }
        //clear
        void clear(){
            this->size = 0;
            return;
        }
        //插入操作，向索引为pos的地方插入value，如果pos大于size，则插入到最后，如果pos小于0，则插入到第一个
        void insert(size_t pos, T value){
            try{
                if(pos>this->size || pos<0){
                    throw std::invalid_argument("index out of range");
                }  else if(pos==this->size){
                    push_back(value);
                } else{
                    if(this->size+1>=this->cap){
                        alloc(this->cap+ADDSIZE);
                        this->cap += ADDSIZE;
                    }
                    for(auto it= this->end()+1;it!=this->get_iter(pos);it--)
                        *it = *(it+(-1));
                    this->data[pos] = value;
                    this->size++;
                }
            } catch (std::invalid_argument& e){
                    std::cout<<"invalid_argument: "<<e.what()<<std::endl;
                    exit(1);
            }
            return;
        }
        //删除操作，删除索引为pos的元素，如果pos大于size，则删除最后一个，如果pos小于0，则删除第一个
        void erase(size_t pos){
            try{
                if(pos>=this->size || pos<0){
                    throw std::invalid_argument("index out of range");
                }
                for(auto it=this->get_iter(pos); it!=this->end(); it++)
                    *it = *(it+1);
                this->size--;
            } catch(std::invalid_argument& e){
                std::cout<<"invalid_argument: "<<e.what()<<std::endl;
                exit(1);
            }
            return; 
        }

        //交换操作，交换两个vector
        void swap(Vec& V){
            T* temp = this->data;
            this->data = V.data;
            V.data = temp;
            size_t temp_size = this->size;
            this->size = V.size;
            V.size = temp_size;
            size_t temp_cap = this->cap;
            this->cap = V.cap;
            V.cap = temp_cap;
            return;
        }

        //访问
        void at(size_t pos){
            try{
                if(pos>=this->size || pos<0){
                    throw std::invalid_argument("index out of range");
                }
                std::cout<<this->data[pos]<<std::endl;
            } catch(std::invalid_argument& e){
                std::cout<<"invalid_argument: "<<e.what()<<std::endl;
                exit(1);
            }
            return;
        }

        //冒泡排序
        void bubble_sort(){
            for(Vec_Iter it=this->begin(); it!=this->end(); it++){
                for(auto it2=it+1; it2!=this->end(); it2++){
                    if(*it>*it2){
                        T temp = *it;
                        *it = *it2;
                        *it2 = temp;
                    }
                }
            }
        }

        //二分查找
        size_t binary_search(T value){
            int left = 0;
            int right = this->size-1;
            while(left<=right){
                int mid = (left+right)/2;
                if(this->data[mid]==value){
                    return mid;
                    break;
                }
                if(this->data[mid]>value){
                    right = mid-1;
                    continue;
                }
                if(this->data[mid]<value){
                    left = mid+1;
                    continue;
                }
            }
            return -1;
        }
        //普通查找，用于字符串，返回第一个匹配的下标，如果不存在返回-1
        size_t find(T value){
            for(Vec_Iter it=this->begin(); it!=this->end(); it++){
                if(*it==value){
                    return it-this->begin();
                }
            }
            return -1;
        }

        //--------------------------------迭代器操作
        //返回迭代器，从第一个元素开始，迭代器可以用于for循环，也可以用于迭代器运算
        Vec_Iter begin(){
            return Vec_Iter(this->data);
        }
        //返回迭代器，从最后一个元素开始，迭代器可以用于for循环，也可以用于迭代器运算
        Vec_Iter end(){
            return Vec_Iter(this->data+this->size);
        }
        //返回指向pos位置的迭代器
        Vec_Iter get_iter(size_t pos){
            return Vec_Iter(this->data+pos);
        }

    
    };
} // namespace MVec
#endif