cmake_minimum_required(VERSION 3.20)

project(anonymous_structs LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(points.exe
    points.c
)
add_compile_options(points.exe
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
)
