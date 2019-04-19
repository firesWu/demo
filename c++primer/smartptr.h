//
// Created by 吴远 on 2019-04-18.
//

#ifndef SECTION3_SMARTPTR_H
#define SECTION3_SMARTPTR_H
#include <iostream>
using namespace std;

class B;
class A {
public:
    B* b;
    shared_ptr<B> b2;
    weak_ptr<B> b3;

    A(){}
    A(B* _b):b(_b){}

    void setB(B* _b){
        b = _b;
    }

    void setB2(shared_ptr<B>& _b){
        b2 = _b;
    }

    void setB3(const weak_ptr<B>& _b){
        b3 = _b;
    }

    ~A(){
        cout<<"A destory"<<endl;
    }
};

class B {
public:
    A* a;
    shared_ptr<A> a2;
    weak_ptr<A> a3;

    B(){}
    B(A* _a):a(_a){}

    void setA(A* _a){
        a = _a;
    }

    void setA2(shared_ptr<A>& _a){
        a2 = _a;
    }

    void setA3(const weak_ptr<A>& _a){
        a3 = _a;
    }

    ~B(){
        cout<<"B destory"<<endl;
    }
};

#endif //SECTION3_SMARTPTR_H
