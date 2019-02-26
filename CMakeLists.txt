cmake_minimum_required(VERSION 3.13)
project(Cryptocurrency)

set(CMAKE_CXX_STANDARD 98)

add_executable(Cryptocurrency main.cpp functions/main_functions.h functions/main_functions.cpp)