//
// Created by 吴远 on 2019-04-18.
//

#ifndef SECTION3_DEMO_H
#define SECTION3_DEMO_H
#include <iostream>
using namespace std;


class demo {
public:
    string value;
    demo():value(""){}
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


};

#endif //SECTION3_DEMO_H
