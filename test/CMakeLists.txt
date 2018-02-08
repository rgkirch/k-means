cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 17)

include_directories(../src)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})
add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=8 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )

#add_executable(everythingTest everythingTest.cpp)

add_executable(kmeansTest kmeansTest.cpp)
target_link_libraries(kmeansTest gtest gtest_main gmock)
add_test(NAME kmeansTestTest COMMAND kmeansTest)

add_executable(directoryIteratorTest directoryIteratorTest.cpp)
target_link_libraries(directoryIteratorTest stdc++fs gtest gtest_main gmock ${ImageMagick_LIBRARIES})
#add_test(NAME directoryIteratorTestTest COMMAND directoryIteratorTest)

add_executable(readRunWriteTest readRunWriteTest.cpp)
target_link_libraries(readRunWriteTest  gtest gtest_main gmock ${ImageMagick_LIBRARIES})
add_test(NAME readRunWriteTestTest COMMAND readRunWriteTest)
