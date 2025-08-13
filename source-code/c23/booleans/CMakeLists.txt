cmake_minimum_required(VERSION 3.10)
project(booleans LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(booleans.exe
    booleans.c
)
target_compile_options(booleans.exe PRIVATE -Wall -Wextra -Wpedantic)
