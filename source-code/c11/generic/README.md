# `_Generic`

`_Generic` is a C11 feature that allows for type-generic programming. It
enables the selection of a function or expression based on the type of its
argument at compile time.


## What is it?

1. `debug_info.c`: application that defines a macro based on `_Generic` to
   print a variable's value and type.
1. `CMakeLists.txt`: CMake file to build the applications.
