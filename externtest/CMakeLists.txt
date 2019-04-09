cmake_minimum_required(VERSION 3.13)
project(externtest)

set(CMAKE_CXX_STANDARD 14)

add_executable(externtest main.cpp head.cpp head.hpp)