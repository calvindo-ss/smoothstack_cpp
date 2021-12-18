cmake_minimum_required(VERSION 3.6)

# The project name
project(bankcli)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)
include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)

# copies users.txt to build/src
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/users.csv
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src)

# copies users.txt to build/src
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/users.csv
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test)