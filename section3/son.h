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

    base(){}

    base(base& b){
        i = 15;
    }
};

class son : public base {
public:
    void test(){
        cout<< " i'm son"<<endl;
    }

    void setI(){
        i = 20;
    }

    void test2(){
        cout<< "hi" <<endl;
    }

};

#endif //SECTION3_SON_H
