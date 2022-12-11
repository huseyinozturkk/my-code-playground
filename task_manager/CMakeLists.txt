PROJECT(task_manager C)

cmake_minimum_required(VERSION 3.1)

include_directories(task_manager
    inc/
)  
add_executable(task_manager
    src/task_manager.c

    test.c
) 

