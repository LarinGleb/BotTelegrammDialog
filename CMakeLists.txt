cmake_minimum_required(VERSION 3.10)
project(Echobot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_executable(echobot Bot.cpp)

include(${CMAKE_SOURCE_DIR}/CMake/clang-format.cmake)

add_subdirectory(SaveFile)
add_subdirectory(CMake)
add_subdirectory(ForTD)
add_subdirectory(LibDB)
add_subdirectory(BotReview)
add_subdirectory(dirVlad)


target_link_libraries(echobot SaveLib)
target_link_libraries(echobot LibDB)
target_link_libraries(echobot ReviewLib)
target_link_libraries(echobot dirVlad)
target_link_libraries(echobot ForTD)


include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})




target_link_libraries(echobot /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})

add_dependencies(echobot ReviewLib SaveLib ForTD dirVlad LibDB)
