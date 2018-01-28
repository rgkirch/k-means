cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 17)

include_directories(../src)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(kmeansTest kmeansTest.cpp)
target_link_libraries(kmeansTest gtest gtest_main gmock)

add_executable(copyImageTest copyImageTest.cpp)
find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})
add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )
target_link_libraries(copyImageTest gtest gtest_main gmock ${ImageMagick_LIBRARIES})