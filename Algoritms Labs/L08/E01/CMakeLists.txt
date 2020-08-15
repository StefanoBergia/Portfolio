cmake_minimum_required(VERSION 3.8)
project(E01)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(E01 ${SOURCE_FILES})

target_link_libraries(E01 m)