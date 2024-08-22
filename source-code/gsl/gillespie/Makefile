CC = gcc
CFLAGS = -O2 -g -std=c99 -Wall
CPPFLAGS = `pkg-config --cflags gsl`
LIBS = `pkg-config --libs gsl`

all: reaction.exe

data: dimer.txt

dimer.txt: reaction.exe
	./$^ > $@

reaction.exe: cl_params_aux.o cl_params.o reaction.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f reaction.exe *.o core dimer.txt
