cmake_minimum_required(VERSION 3.10)

project(DB CXX)

set(Boost_USE_MULTITHREADED ON)

add_library(LibDB SHARED DB.cpp)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)

include_directories(/usr/local/include /usr/local/mysql/connector-c++-/include/mysqlx/ /usr/local/mysql/connector-c++-/include/mysql/ ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

target_include_directories(LibDB 
                           PUBLIC /usr/local/mysql/connector-c++-/include/mysql/
                           PUBLIC /usr/local/mysql/connector-c++-/include/mysqlx/)

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR /usr/local/mysql/connector-c++-/)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64)

target_link_libraries(LibDB /usr/local/mysql/connector-c++-/lib64/debug/libmysqlcppconn.so.9.8.0.26 /usr/local/mysql/connector-c++-/lib64/debug/libmysqlcppconn8.so.2.8.0.26 ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
