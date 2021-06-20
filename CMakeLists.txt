cmake_minimum_required(VERSION 3.19)
project(exam)

set(CMAKE_CXX_STANDARD 14)

add_executable(exam main.cpp MyList.h Container.h Algorithms.h Iterator.h)