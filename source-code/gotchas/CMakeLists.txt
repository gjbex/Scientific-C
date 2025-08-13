cmake_minimum_required(VERSION 3.10)
project(gotchas C)

# Use C99 to match typical settings for these examples
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Option to include the intentionally failing 'errors' target
option(BUILD_ERRORS "Build the 'errors' target with intentional compile errors" OFF)

add_executable(const_int_ptr_vs_int_const_ptr
    const_int_ptr_vs_int_const_ptr.c
)
target_compile_options(const_int_ptr_vs_int_const_ptr PRIVATE -Wall -Wextra -Wpedantic)
set_target_properties(const_int_ptr_vs_int_const_ptr PROPERTIES
    RUNTIME_OUTPUT_NAME "const_int_ptr_vs_int_const_ptr.exe"
)

# Executable: float_vs_double (additional similar rule)
add_executable(float_vs_double
    float_vs_double.c
)
target_compile_options(float_vs_double PRIVATE -Wall -Wextra -Wpedantic)
# Link libm for sin/sinf and librt for clock_gettime
target_link_libraries(float_vs_double PRIVATE m rt)
set_target_properties(float_vs_double PROPERTIES
    RUNTIME_OUTPUT_NAME "float_vs_double.exe"
)

if(BUILD_ERRORS)
    # Compiles only, with COMPILE_ERROR defined to surface intended errors
    add_library(errors OBJECT
        const_int_ptr_vs_int_const_ptr.c
    )
    target_compile_definitions(errors PRIVATE COMPILE_ERROR)
    target_compile_options(errors PRIVATE -O2 -g -Wall -Wextra)
endif()
