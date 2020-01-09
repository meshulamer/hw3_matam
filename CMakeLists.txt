cmake_minimum_required(VERSION 3.15)
project(hw3_matam)

set(CMAKE_CXX_STANDARD 11)

add_executable(hw3_matam UniqueArray.h UniqueArrayImp.h OurUATests.cpp)