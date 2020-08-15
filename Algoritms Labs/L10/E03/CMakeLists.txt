cmake_minimum_required(VERSION 3.8)
project(E03)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c ST.c ST.h Item.c Item.h Graph.c Graph.h)
add_executable(E03 ${SOURCE_FILES})