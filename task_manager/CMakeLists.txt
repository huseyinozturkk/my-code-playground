cmake_minimum_required(VERSION 3.10)

project(task_manager)

include_directories(task_manager 
    inc/
    )

add_executable(task_manager 
    test.c
    src/task_manager.c
    )