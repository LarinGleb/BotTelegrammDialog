cmake_minimum_required(VERSION 3.10)

add_library(dirVlad SHARED bot_guide.cpp)

add_to_target_clang(${CMAKE_SOURCE_DIR}/dirVlad/bot_guide.cpp)