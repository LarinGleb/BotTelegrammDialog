cmake_minimum_required(VERSION 3.10)

add_library(ForTD SHARED PPForTD.cpp)

add_to_target_clang(${CMAKE_SOURCE_DIR}/ForTd/PPForTD.h)
