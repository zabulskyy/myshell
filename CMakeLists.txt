cmake_minimum_required(VERSION 3.0)
project(myshell)

set(CMAKE_CXX_STANDARD 11)


find_package(Boost COMPONENTS program_options filesystem regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(src)

add_executable(myshell src/main.cpp)
add_executable(myrm src/myrm.cpp)
add_executable(mycat src/mycat.cpp)
add_executable(myhello src/myhello.cpp)
add_executable(mymkdir src/mymkdir.cpp)
add_executable(myls src/myls.cpp)

target_link_libraries(myrm ${Boost_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY})
target_link_libraries(mymkdir ${Boost_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY})
