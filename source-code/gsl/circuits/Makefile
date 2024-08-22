CC = gcc
override CFLAGS += -O2 -g
CPPFLAGS = $(shell pkg-config --cflags gsl)
LDFLAGS = $(shell pkg-config --libs gsl)
LIBS =

all: circuit_01.exe circuit_02.exe

data: resistance.txt

resistance.txt: circuit_01.exe
	./$^ > $@

%.exe: %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

clean:
	rm -f *.exe *.o core resistance.txt
