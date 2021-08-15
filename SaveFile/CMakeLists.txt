cmake_minimum_required(VERSION 3.10)
project(SaveTestP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")
set(Boost_USE_MULTITHREADED ON)

add_library(SaveLib SHARED SaveFile.cpp)

add_to_target_clang(${CMAKE_SOURCE_DIR}/SaveFile/SaveFile.cpp)
add_to_target_clang(${CMAKE_SOURCE_DIR}/SaveFile/SaveFile.h)

add_executable(SaveTest tests/SaveFileTest.cpp SaveFile.cpp)

enable_testing()

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(SaveTest ${GTEST_LIBRARIES} Threads::Threads)
add_test(SaveTest "./TestSave")
