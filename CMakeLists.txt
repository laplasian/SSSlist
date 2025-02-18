cmake_minimum_required(VERSION 3.28)
project(boundlist C)

set(CMAKE_C_STANDARD 11)

add_executable(boundlist main.c
        slist.c
        slist.h
        tests.c
        tests.h)
