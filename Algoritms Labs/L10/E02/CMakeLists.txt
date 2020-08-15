cmake_minimum_required(VERSION 3.8)
project(E02)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c BST.c BST.h Utente.c Utente.h)
add_executable(E02 ${SOURCE_FILES})