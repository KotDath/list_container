cmake_minimum_required(VERSION 3.19)
project(exam)

set(CMAKE_CXX_STANDARD 20)

include_directories(Exceptions)

add_executable(exam Algorithms.h Container.h Iterator.h main.cpp Exceptions/RemoveException.h Exceptions/BadIteratorException.h)