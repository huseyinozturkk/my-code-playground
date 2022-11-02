cmake_minimum_required(VERSION 3.10)

project(modular)

include_directories(modular 
    inc/
    )

add_executable(modular 
    src/main.c
    src/mylib.c
    )