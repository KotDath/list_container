cmake_minimum_required(VERSION 3.19)
project(stl)

set(CMAKE_CXX_STANDARD 17)

add_executable(stl Main.cpp Container.h Iterator.h Algorithms.h)