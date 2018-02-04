cmake_minimum_required(VERSION 3.6)

project(kmeans)

#include_directories(src)
#add_subdirectory(src)
add_subdirectory(lib/googletest)
add_subdirectory(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lstdc++fs")