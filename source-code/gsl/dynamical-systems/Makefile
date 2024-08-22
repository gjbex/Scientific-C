CC = gcc
override CFLAGS += -O2 -g -std=c99 -Wall
CPPFLAGS = `pkg-config --cflags gsl`
LDFLAGS = `pkg-config --libs gsl`

APPL = linear-oscillator.exe gsl-linear-oscillator.exe \
       gsl-nonlinear-oscillator.exe gsl-poincare.exe
CL_OBJS = cl_params.o cl_params_aux.o

all: $(APPL)

%.exe: $(CL_OBJS) %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

weave: param_defs.txt
	weave -l C -d $<

clean:
	rm -f *.o *.exe core normal[12].txt chaos[12].txt \
        lyapunov_normal.txt lyapunov_chaos.txt \
        poincare_chaos.txt poincare_normal.txt \
        linear.txt nonlinear.txt

data: lin_vs_nonlin lyapunov poincare

.PHONY: lyapunov
lyapunov: lyapunov_normal.txt lyapunov_chaos.txt

lyapunov_normal.txt: normal1.conf normal2.conf gsl-nonlinear-oscillator.exe
	./gsl-nonlinear-oscillator.exe normal1.conf > normal1.txt
	./gsl-nonlinear-oscillator.exe normal2.conf > normal2.txt
	./lyapunov.py normal1.txt normal2.txt > $@

lyapunov_chaos.txt: chaos1.conf chaos2.conf gsl-nonlinear-oscillator.exe
	./gsl-nonlinear-oscillator.exe chaos1.conf > chaos1.txt
	./gsl-nonlinear-oscillator.exe chaos2.conf > chaos2.txt
	./lyapunov.py chaos1.txt chaos2.txt > $@

.PHONY: poincare
poincare: poincare_normal.txt poincare_chaos.txt

poincare_normal.txt: normal1.conf gsl-poincare.exe
	./gsl-poincare.exe normal1.conf > $@

poincare_chaos.txt: chaos1.conf gsl-poincare.exe
	./gsl-poincare.exe chaos1.conf > $@

.PHONY: lin_vs_nonlin
lin_vs_nonlin: linear.txt nonlinear.txt

linear.txt: large-oscillations.conf gsl-linear-oscillator.exe
	./gsl-linear-oscillator.exe large-oscillations.conf > $@

nonlinear.txt: large-oscillations.conf gsl-nonlinear-oscillator.exe
	./gsl-nonlinear-oscillator.exe large-oscillations.conf > $@
