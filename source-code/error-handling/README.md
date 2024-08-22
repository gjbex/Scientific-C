# ErrorHandling
A few illustration of error handling.

## What is  it?
1. `allocation_error.c`: illustration of error handling in the context
    of dynamic memory management for C.
1. `command_line_args_error.c`: illustrates undefined behaviour of
`   `atol` et al., and illustrating `strtol` alternative.
1. ``file_error.c`: illustrates error handling in the context of
    file I/O in C.
1. `ieee_exceptions.c`: C application to illustrate how to detect
    IEEE floating point exceptions using `fetestexcept`.
1. `ieee_functions.c`: C application to illustrate how to detect
    IEEE floating point exceptions using `isnormal`.
1. `overflow_sum.c`: C application to illustrate more real-world
    example of detecting IEEE floating point overflow exception.
1. `read_error_incorrect.c`: illustration of the problems caused by
    not checking the result of `fscanf`.
1. `read_error.c`: illustration of how a check of the return value
    of fascanf catches problems in the input.
1. `input_ok.txt`: input file that is valid for `read_error.exe`.
1. `input_incomplete.txt`: input file that is incomplete for
    `read_error.exe`.
1. `input_nok.txt`: input file that is not valid for `read_error.exe`.
