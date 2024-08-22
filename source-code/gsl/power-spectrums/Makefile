CC = gcc
CFLAGS = -O2 -g -Wall -std=c99
CPPFLAGS = `pkg-config --cflags gsl`
LDFLAGS = `pkg-config --libs gsl`
LIBS =

APPL = power_spectrum.exe
DATA_FILES = signal1.txt signal2.txt \
             power_spectrum1.txt power_spectrum2.txt \
             example_signal.txt example_spectrum.txt
OBJS = 

all: $(APPL)

%.exe: $(OBJS) %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(APPL) $(OBJS) core $(DATA_FILES)


data: power_spectrum.exe
	./signal.py --f 120.0 260.6 440.0 1500.0 \
	            --A   1.0   0.8   0.1    0.3 \
	    > signal1.txt
	./signal.py --f 440.0 --A 1.0 --noise 0.05 > signal2.txt
	./signal.py --f 435.0 445.0 --A 1.0 0.5 --header > example_signal.txt
	./power_spectrum.exe signal1.txt > power_spectrum1.txt
	./power_spectrum.exe signal2.txt > power_spectrum2.txt
	./power_spectrum.exe example_signal.txt > example_spectrum.txt
