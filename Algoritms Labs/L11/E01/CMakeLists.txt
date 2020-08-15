cmake_minimum_required(VERSION 3.8)
project(E01)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c ST.c ST.h Graph.c Graph.h PQ.c PQ.h Edge.c Edge.h)
add_executable(E01 ${SOURCE_FILES})