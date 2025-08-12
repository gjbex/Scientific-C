cmake_minimum_required(VERSION 3.20)

project(generic LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(debug_info.exe
    debug_info.c
)
