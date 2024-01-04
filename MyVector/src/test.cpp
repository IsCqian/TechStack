#include"test.h"
#include<iostream>
#include<vector>
#include<chrono>
//构造函数的检验
void create_test(){
    int *arr= new int[5];
    arr[0]=1;
    arr[1]=2;
    arr[2]=3;
    arr[3]=4;
    arr[4]=5;

    //默认构造函数测试
    std::cout<<"默认构造函数测试"<<std::endl;
    MVec::Vec<int> vec1;
    vec1.show_vec();
    std::cout<<std::endl;

    //用new出的数组初始化形式测试
    std::cout<<"用new出的数组初始化形式测试"<<std::endl;
    MVec::Vec<int> vec2(arr,5);
    vec2.show_vec();
    std::cout<<std::endl;

    //拷贝构造测试
    std::cout<<"拷贝构造测试"<<std::endl;
    MVec::Vec<int> vec3(vec2);
    vec3.show_vec();
    std::cout<<std::endl;

    //创建给定初始大小的容器测试
    std::cout<<"创建给定初始大小的容器测试"<<std::endl;
    MVec::Vec<int> vec4(5);
    vec4.show_vec();
    std::cout<<std::endl;

    //移动构造测试
    std::cout<<"移动构造测试"<<std::endl;
    MVec::Vec<int> vec5(std::move(vec3));
    vec5.show_vec();
    std::cout<<std::endl;

    //n个val的构造测试
    std::cout<<"n个val的构造测试"<<std::endl;
    MVec::Vec<int> vec6(5,1);
    vec6.show_vec();
    std::cout<<std::endl;

    //带参数列表的构造函数
    std::cout<<"带参数列表的构造函数"<<std::endl;
    MVec::Vec<int> vec7 = {1,2,3,4,5};
    vec7.show_vec();
    std::cout<<std::endl;
}

//效率测试
void Efficiency_Testing(){
    std::cout<<"*********************测试开始"<<"*********************"<<std::endl;
    MVec::Vec<int> vec1;
    std::vector<int> vec2;

    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0;i<1000000;i++){
        vec1.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> mvec_create_time = end - start;

    start = std::chrono::high_resolution_clock::now();
    for(int i=0;i<1000000;i++){
        vec2.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> svec_create_time = end - start;

    start = std::chrono::high_resolution_clock::now();
    for(int i=0;i<1000000;i++){
        vec1.pop_back();
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> mvec_pop_time = end - start;

    start = std::chrono::high_resolution_clock::now();
    for(int i=0;i<1000000;i++){
        vec2.pop_back();
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> svec_pop_time = end - start;
    std::cout<<"mvec_create_time: "<<mvec_create_time.count()<<std::endl;
    std::cout<<"svec_create_time: "<<svec_create_time.count()<<std::endl;
    std::cout<<"mvec_pop_time: "<<mvec_pop_time.count()<<std::endl;
    std::cout<<"svec_pop_time: "<<svec_pop_time.count()<<std::endl;


    return ; 
}  

//增删查改测试
void add_delete_search_test(){
    MVec::Vec<int> vec = {7,4,9,6,0};
    std::cout<<"原数据："<<std::endl;
    vec.show_vec();
    std::cout<<std::endl;

    vec.push_back(1);
    std::cout<<"push_back(1)后数据："<<std::endl;
    vec.show_vec();
    std::cout<<std::endl;

    vec.pop_back();
    std::cout<<"pop_back()后数据："<<std::endl;
    vec.show_vec();
    std::cout<<std::endl;

    vec.insert(3,2);
    std::cout<<"insert(3,2)后数据："<<std::endl;
    vec.show_vec();
    std::cout<<std::endl;

    vec.erase(3);
    std::cout<<"erase(3)后数据："<<std::endl;
    vec.show_vec();
    std::cout<<std::endl;

    vec.bubble_sort();
    std::cout<<"bubble_sort()后数据："<<std::endl;
    vec.show_vec();
    std::cout<<std::endl;

    size_t pos = vec.binary_search(9);
    std::cout<<"binary_search(9)后数据返回的数据:"<<pos<<std::endl;
    std::cout<<std::endl;

    vec[1] = 3;
    std::cout<<"vec[1] = 3后数据:"<<std::endl;
    vec.show_vec();
    std::cout<<std::endl;
    std::cout<<"使用at访问vec[1]: "<<std::endl;
    vec.at(1);
}
