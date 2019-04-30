//
// Created by 吴远 on 2019-04-18.
//

#ifndef SECTION3_SON_H
#define SECTION3_SON_H
#include <iostream>
using namespace std;

class base {
public:
    int i = 0;
    virtual void test(){
        cout<< "i'm father" <<endl;
    }

    virtual void setI(){
        i = 10;
    }

    void test3(){
        cout<<"hi test3"<<endl;
    }

    base(){
        cout<< "default" <<endl;
    }

    base(const base& b){
        cout<<"copy"<<endl;
    }

    base& operator=(const base& b){
        cout<<" = "<<endl;
        return *this;
    }

    void test4();
};

class son : public base {
public:
    int i = 0;
    void test(){
        cout<< " i'm son"<<endl;
    }

    void setI(){
        i = 20;
    }

    void test2(){
        cout<< "hi" <<endl;
    }

    son(){}

};

#endif //SECTION3_SON_H
