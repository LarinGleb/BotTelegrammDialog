cmake_minimum_required(VERSION 3.10)

project(study)
include(${CMAKE_SOURCE_DIR}/CMake/clang-format.cmake)

add_subdirectory(gleb)
get_property(LIST_FILES GLOBAL PROPERTY LIST_FILES)

add_custom_target(
        clang-force-format
        COMMAND /usr/bin/clang-format -style=webkit -i  ${LIST_FILES}
)