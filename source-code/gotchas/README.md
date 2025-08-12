# Misc
Some illustrations of miscellaneous C features.

## What is it?
1. `const_int_ptr_vs_int_const_ptr.c`: illustration of semantics of
    `const int*` versus `int * const`.
1. `single_vs_double.c`: illustration of the difference between single and double
   floating point numbers.
1. `CMakeLists.txt`: CMake file to build the applications.

## How to use it?

To build the code:
```bash
$ cmake -B build/ -S .
$ cmake --build build/
```

To get some cmopiler errors, use:
```bash
$ cmake -B build/ -S . -DBUILD_ERRORS=ON
```
