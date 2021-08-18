cmake_minimum_required(VERSION 3.10)

add_library(bottimelibc SHARED BotTime.cpp)

add_to_target_clang(${CMAKE_SOURCE_DIR}/bottimelib/BotTime.cpp)
add_to_target_clang(${CMAKE_SOURCE_DIR}/bottimelib/BotTime.h)