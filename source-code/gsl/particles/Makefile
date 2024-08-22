CC = gcc
CFLAGS = -O2 -g
CPPFLAGS = `pkg-config --cflags gsl`
LDFLAGS = `pkg-config --libs gsl`
LIBS =

all: generate_particles.exe compute_properties_01.exe \
     compute_properties_02.exe dynamics.exe ode.exe

data: trajectories.txt ode_trajectories.txt

trajectories.txt: dynamics.exe
	./$^ 2 1000 < two_particles.txt > $@

ode_trajectories.txt: ode.exe
	./$^ 2 1000 < two_particles.txt > $@

ode.exe: particles.c ode.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

dynamics.exe: particles.c dynamics.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

compute_properties_02.exe: particles.c compute_properties_02.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.exe: %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

clean:
	rm -f *.exe *.o core trajectories.txt ode_trajectories.txt
