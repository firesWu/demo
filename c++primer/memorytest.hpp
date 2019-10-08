#ifndef MEMORY_TEST
#define MEMORY_TEST

#include <iostream>

class memorytest {

public:
    memorytest(){
        std::cout<<" init " <<std::endl;
    }

    static void* operator new(size_t size) {
        std::cout<< " memory allocate by man " << std::endl;
        if(size == 0){
            size = 1;
        }
        return ::malloc(size);
    }

    static void operator delete(void* ptr) {
        std::cout<< " memory free by man " << std::endl;
        free(ptr);
    }

};

#endif