//
// Created by 吴远 on 2019-04-25.
//

#ifndef SECTION3_FRIEND_H
#define SECTION3_FRIEND_H
#include <iostream>
using namespace std;

class friend_demo1;
class friend_demo2 {
public:
    friend_demo2(){}

    void getI(friend_demo1& fd1);

    void getI2(friend_demo1& fd1);
};

class friend_demo1 {
public:
    friend_demo1(){
        i = 10;
    }
private:
    int i;

    friend void friend_demo2::getI2(friend_demo1& fd1);
};

void friend_demo2::getI2(friend_demo1 &fd1) {
    cout<<fd1.i<<endl;
}



#endif //SECTION3_FRIEND_H
