#include <stdio.h>
#include <string.h>

#define DEBUG_INFO(msg, value) \
{ \
    fprintf(stderr, "DEBUG: %s: %s = ", __FILE__, msg); \
    char *format = _Generic((value), \
        int: "%d", \
        long: "%ld", \
        float: "%f", \
        double: "%f", \
        char*: "%s", \
        default: "%s" \
    ); \
    fprintf(stderr, format, value); \
    fprintf(stderr, "\n"); \
}


int main() {
    int int_value = 42;
    long long_value = 1234567890L;
    float float_value = 3.14f;
    double double_value = 2.718281828459;
    char *string_value = "Hello, World!";

    DEBUG_INFO("int_value", int_value);
    DEBUG_INFO("long_value", long_value);
    DEBUG_INFO("float_value", float_value);
    DEBUG_INFO("double_value", double_value);
    DEBUG_INFO("string_value", string_value);

    return 0;
}   
