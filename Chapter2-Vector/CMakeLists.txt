cmake_minimum_required(VERSION 3.12)
project(Chapter2_Vector)

set(CMAKE_CXX_STANDARD 11)

add_executable(Chapter2_Vector main.cc Fibonacci.h Vector.cpp Vector.hpp)
