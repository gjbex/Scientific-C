CC = gcc
CFLAGS = -O2 -g -Wall -std=c99
LIBS = -lm

APPL = julia.exe julia_iterate.exe
DATA = julia.txt conv.txt non_conv.txt

all: $(APPL)

%.exe: %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

data: $(DATA)

conv.txt: julia_iterate.exe
	./$^ 0.5 0.5 > $@

non_conv.txt: julia_iterate.exe
	./$^ 0.5 0.7 10 > $@

%.txt: %.exe
	./$^ 2048 > $@

clean:
	rm -f *.o $(APPL) $(DATA)
