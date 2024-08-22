CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -O2
LDLIBS = -lm

all: allocation_error.exe command_line_args_error.exe file_error.exe \
	 read_error.exe read_error_incorrect.exe ieee_exceptions.exe \
	 overflow_sum.exe ieee_functions.exe

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)
	$(RM) $(wildcard core.*) core
