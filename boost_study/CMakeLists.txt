cmake_minimum_required(VERSION 3.13)
project(boost_study)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/include)

link_directories(/usr/local/lib)

add_executable(boost_study main.cpp io_service.hpp thread_test.hpp)

target_link_libraries(boost_study boost_thread-mt boost_system)