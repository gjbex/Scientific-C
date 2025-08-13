cmake_minimum_required(VERSION 3.10)
project(bitints LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(counter_8.exe
    counter_8.c
)
target_compile_options(counter_8.exe PRIVATE -Wall -Wextra -Wpedantic)

add_executable(addition.exe
    addition.c
)
target_compile_options(addition.exe PRIVATE -Wall -Wextra -Wpedantic)
