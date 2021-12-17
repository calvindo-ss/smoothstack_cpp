cmake_minimum_required(VERSION 3.6)

# The project name
project(bankcli)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)

add_subdirectory(src)
add_subdirectory(test)

# copies users.txt to build/src
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/users.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src)

# copies users.txt to build/src
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/users.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test)