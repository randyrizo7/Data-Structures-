cmake_minimum_required(VERSION 3.23)
project(p4)

set(CMAKE_CXX_STANDARD 14)

add_executable(p4 p4.cpp CommonWordList.h WordCounter.h)
