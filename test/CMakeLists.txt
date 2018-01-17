cmake_minimum_required(VERSION 3.6)

include_directories(../src)
add_executable(kmeansTest kmeansTest.cpp)
target_link_libraries(kmeansTest gtest gtest_main gmock)