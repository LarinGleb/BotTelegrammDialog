cmake_minimum_required(VERSION 3.10)

add_library(SaveLib SHARED SaveFile.cpp)

add_to_target_clang(${CMAKE_SOURCE_DIR}/SaveFile/SaveFile.cpp)
add_to_target_clang(${CMAKE_SOURCE_DIR}/SaveFile/SaveFile.h)

