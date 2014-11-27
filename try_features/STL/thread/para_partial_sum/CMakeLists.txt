
cmake_minimum_required(VERSION 2.8)
project(para_partial_sum)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O3")

add_executable(t main.cpp)

