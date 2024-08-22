CC = gcc
CFLAGS = -O2 -g -Wall -std=c99
CPPFLAGS = `pkg-config --cflags gsl`
GSL_LIBS = `pkg-config --libs gsl`
LIBS = -lm

all: average.exe fac.exe dec_to_bin.exe dec_to_bin_recursive.exe norm.exe \
     scalar_product.exe quad.exe quad_gsl.exe circle.exe complex_c89.exe \
     complex_c99.exe bin_to_dec.exe

%_gsl.exe: %_gsl.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(GSL_LIBS)

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f *.exe *.o core.*
