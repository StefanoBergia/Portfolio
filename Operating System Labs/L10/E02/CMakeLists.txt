cmake_minimum_required(VERSION 3.8)
project(E02)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(E02 ${SOURCE_FILES})
target_link_libraries(E02 pthread)