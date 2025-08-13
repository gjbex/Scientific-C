cmake_minimum_required(VERSION 3.10)
project(int_arithmetic_overflow LANGUAGES C)

# Use C99 to match typical settings for these examples
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
# for timing functions like clock_gettime
set(CMAKE_C_EXTENSIONS ON)

add_executable(check_overflow.exe
    check_overflow.c
)
target_compile_options(check_overflow.exe PRIVATE -Wall -Wextra -Wpedantic)
# Link libm for for clock_gettime
target_link_libraries(check_overflow.exe PRIVATE rt)
