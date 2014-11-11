
cmake_minimum_required(VERSION 2.9)

project(static_init)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

add_executable(t static_init.cpp)

