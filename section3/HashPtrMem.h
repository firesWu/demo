//
// Created by 吴远 on 2019-04-18.
//

#ifndef SECTION3_HASHPTRMEM_H
#define SECTION3_HASHPTRMEM_H
#include <iostream>
using namespace std;

class HasPtrMem {
public:
    HasPtrMem():d(new int(0)){
        cout<<"construct"<<endl;
    }

    // 增加深拷贝函数， 避免 d 指针成为悬挂指针
    HasPtrMem(HasPtrMem& a):d(new int(*a.d)){
        cout<<"construct"<<endl;
    }

    ~HasPtrMem(){
        delete d;
        cout<<"destrcut"<<endl;
    }
    int * d;
};

#endif //SECTION3_HASHPTRMEM_H
