CC = gcc
override CFLAGS += -O2 -g -Wall -std=c99
CPPFLAGS =
LDFLAGS =
LIBS = -lm

APPL = walk.exe entropy.exe
OBJS = particle.o cl_params_aux.o cl_params.o distribution.o util.o stats.o
UNCONSTRAINED = very_short_run_unconstrained.txt \
                short_run_unconstrained.txt \
                medium_run_unconstrained.txt \
                long_run_unconstrained.txt
CONSTRAINED = very_short_run_constrained.txt \
              short_run_constrained.txt \
              medium_run_constrained.txt \
              long_run_constrained.txt
ENTROPY = entropy_constrained.txt entropy_unconstrained.txt

all: $(APPL)

clean:
	rm -f $(OBJS) $(APPL) core $(UNCONSTRAINED) $(CONSTRAINED) $(ENTROPY)

data: unconstrained_data constrained_data entropy_data

unconstrained_data: walk.exe $(UNCONSTRAINED)

%_run_unconstrained.txt: %_run_unconstrained.conf
	./walk.exe $< > $@

constrained_data: walk.exe $(CONSTRAINED)

%_run_constrained.txt: %_run_constrained.conf
	./walk.exe $< > $@

entropy_data: entropy.exe $(ENTROPY)

entropy_%.txt: long_run_%.conf entropy.exe
	./entropy.exe $< > $@

%.exe: %.o $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
