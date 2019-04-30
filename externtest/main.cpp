#include <iostream>
#include "head.hpp"
#include "enum.h"
#include <vector>

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
//    std::cout<<test6(1,2) << std::endl;


    // test &
    int ival = 2;
    int ival2 = 4;
    int& refval = ival;
    std::cout<< refval << std::endl;
    refval = ival2;
    refval = 6;
    std::cout<< ival2 << std::endl;
    const int& refval2 = ival;
    ival = 10;


    std::cout<< status_enum::sucess << std::endl;

    std::vector<int> a;
    a.emplace_back(1);
    return 0;
}
