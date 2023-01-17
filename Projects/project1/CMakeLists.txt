cmake_minimum_required(VERSION 3.23)
project(project1)

set(CMAKE_CXX_STANDARD 14)

add_executable(project1 p1.cpp BookList.cpp BookList.h MemberList.cpp MemberList.h RatingList.cpp RatingList.h)
