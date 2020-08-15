cmake_minimum_required(VERSION 3.8)
project(L01)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c BST.h BST.c Item.c Item.h)
add_executable(L01 ${SOURCE_FILES})