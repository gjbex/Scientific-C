CC = gcc
CFLAGS = -O2 -g
CPPFLAGS =
LDFLAGS =
LIBS = -lm

DATA = analytic.txt euler.txt energy.txt corrected.txt air_drag.txt \
       density.txt ode.txt range.txt

all: cannon_01.exe cannon_02.exe cannon_03.exe cannon_04.exe \
     cannon_05.exe cannon_06.exe cannon_ode.exe cannon_ode_2.exe \
     cannon_max_range.exe cannon_range.exe

data: $(DATA)

analytic.txt: cannon_01.exe
	./$^ 1.0 > $@

euler.txt: cannon_02.exe
	./$^ 1.0 > $@

energy.txt: cannon_03.exe
	./$^ 1.0 > $@

corrected.txt: cannon_04.exe
	./$^ 1.0 > $@

air_drag.txt: cannon_05.exe
	./$^ 1.0 > $@

density.txt: cannon_06.exe
	./$^ 1.0 > $@

ode.txt: cannon_ode.exe
	./$^ 1.0 > $@

range.txt: cannon_range.exe
	./$^ > $@

cannon_ode.exe: cannon_ode.c
	$(CC) $(CFLAGS) `pkg-config --cflags gsl` -o $@ $^ \
	      `pkg-config --libs gsl`

cannon_ode_2.exe: cannon_ode_2.c
	$(CC) $(CFLAGS) `pkg-config --cflags gsl` -o $@ $^ \
	      `pkg-config --libs gsl`

cannon_max_range.exe: cannon_max_range.c
	$(CC) $(CFLAGS) `pkg-config --cflags gsl` -o $@ $^ \
	      `pkg-config --libs gsl`

cannon_range.exe: cannon_range.c
	$(CC) $(CFLAGS) `pkg-config --cflags gsl` -o $@ $^ \
	      `pkg-config --libs gsl`

%.exe: %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

clean:
	rm -f *.exe *.o core $(DATA)
