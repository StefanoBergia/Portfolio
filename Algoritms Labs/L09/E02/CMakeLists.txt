cmake_minimum_required(VERSION 3.8)
project(L02)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c Item.c Item.h PQ.c PQ.h)
add_executable(L02 ${SOURCE_FILES})
target_link_libraries(L02 m)