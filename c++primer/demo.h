//
// Created by 吴远 on 2019-04-18.
//

#ifndef SECTION3_DEMO_H
#define SECTION3_DEMO_H
#include <iostream>
using namespace std;


static int global_count = 0;

class demo {
public:
    typedef string ss;
    string value;
    demo():value(""){
        cout<<" default constructor "<<endl;
    }
    demo( string b ):value(b){
        cout<<" call constructor " <<endl;
    }


    demo( demo& b ):value(b.value){
        cout<<" call copy constructed"<<endl;
    }

    demo( const demo& b ):value(b.value){
        cout<<" call copy const constructed"<<endl;
    }

    demo( demo&& b ){
        value = move(b.value);
        cout<<" call move constructed"<<endl;
    }

    ~demo(){
        cout<<" destroy demo"<<endl;
    }

    void test(){
        cout<<"hi test"<<endl;
    }

    int add(int a, int b){
        cout<< ++global_count <<endl;
        cout<<value<<endl;
        return 0;
    }

    int add(int a, int b) const{
        cout<<this->value<<endl;
        return a + b;
    }


    static int hi(){
        return si;
    }

private:
    static int si;
};

int demo::si = 2;

class demo2 {
public:
    explicit demo2(){
        cout<<"default constructor"<<endl;
    }

    explicit demo2(const demo2& d){
        cout<<"std"<<endl;
    }

    demo2(const demo2&& d){
        cout<<"haha"<<endl;
    }
};

class demo3 {
public:
    int *i;
    demo3(){
        i = new int(5);
    }

    demo3& operator=(demo3& d){
        i = d.i;
        return *this;
    }
//    ~demo3(){
//        cout<<i<<endl;
//    }
};


class demo4 {
public:
    int i;
    demo4(){}
    demo4(int _i ){
        i = _i;
    }

    demo4(const demo4& b ){
        i = b.i;
        cout<<"copy"<<endl;
    }

//    friend demo4 operator+(const demo4& a, const demo4& b){
//        demo4 d;
//        d.i = a.i + b.i;
//        return d;
//    }

    demo4 operator+(const demo4& b){
        cout<<"+"<<endl;
        i+= b.i;
        return *this;
    }

};

#endif //SECTION3_DEMO_H
