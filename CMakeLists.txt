cmake_minimum_required(VERSION 3.15)
project(heaps)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(src)
add_executable(heaps test.cpp)
target_link_libraries(heaps gtest gtest_main)