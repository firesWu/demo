#include <iostream>
#include "head.hpp"

extern const int test;
extern int test2();
extern int test3;
//extern const int test4;

// compile is right, but linki is wrong
//extern int test6(int a, int b);

int main() {
    // test global scope
    std::cout << test << std::endl;
    std::cout << test2() << std::endl;
    std::cout << test3 << std::endl;
//    std::cout << test4 << std::endl;
    std::cout << test5() << std::endl;
    std::cout<<test6(1,2) << std::endl;


    return 0;
}