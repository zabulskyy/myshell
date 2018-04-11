cmake_minimum_required(VERSION 3.5)
project(myshell)

set(CMAKE_CXX_STANDARD 11)


find_package(Boost COMPONENTS program_options filesystem regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(myshell main.cpp)

set(RUNTIME_OUTPUT_DIRECTORY ./bin)
set(IMPORTED_LOCATION ./src)

add_executable(myrm ./src/myrm.cpp)
add_executable(mycat ./src/mycat.cpp)
add_executable(myhello ./src/myhello.cpp)

target_link_libraries(myrm ${Boost_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY})
