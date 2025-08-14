cmake_minimum_required(VERSION 3.10)
project(typeof LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(swap.exe
    swap.c
)
target_compile_options(swap.exe PRIVATE -Wall -Wextra -Wpedantic)

