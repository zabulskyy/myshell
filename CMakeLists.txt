cmake_minimum_required(VERSION 3.9)
project(myshell)

set(CMAKE_CXX_STANDARD 11)

add_executable(myshell main.cpp modules/myhello.cpp my_modules.cpp my_modules.h)