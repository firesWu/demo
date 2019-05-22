//
// Created by firesWu on 2019-05-22.
//

#ifndef BOOST_STUDY_THREAD_TEST_HPP
#define BOOST_STUDY_THREAD_TEST_HPP

#include <iostream>
#include <chrono>
#include <thread>

void independentThread()
{
    std::cout << "Starting concurrent thread.\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Exiting concurrent thread.\n";
}

void threadCaller()
{
    std::cout << "Starting thread caller.\n";
    std::thread t(independentThread);
    t.detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Exiting thread caller.\n";
}

int thread_test()
{
    threadCaller();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "back to main.\n";
}

#endif //BOOST_STUDY_THREAD_TEST_HPP
