cmake_minimum_required(VERSION 3.8)
project(E04)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c es.c es.h atl.c atl.h esList.c esList.h esArray.c esArray.h atlList.c atlList.h)
add_executable(E04 ${SOURCE_FILES})