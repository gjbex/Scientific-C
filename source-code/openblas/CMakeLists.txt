cmake_minimum_required(VERSION 3.10)
project(openblas LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

find_package(BLAS REQUIRED)

add_executable(dgemm.exe
    dgemm.c
)
target_compile_options(dgemm.exe PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(dgemm.exe PRIVATE BLAS::BLAS)
target_include_directories(dgemm.exe PRIVATE ${BLAS_INCLUDE_DIRS})
