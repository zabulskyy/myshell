cmake_minimum_required(VERSION 3.9)
project(forkexec)

set(CMAKE_CXX_STANDARD 14)

add_executable(runner runner_main.cpp)
add_executable(victim victim_main.cpp)