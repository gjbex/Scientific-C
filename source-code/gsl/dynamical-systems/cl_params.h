#ifndef CL_PARAMS_HDR
#define CL_PARAMS_HDR

#include <stdio.h>

typedef struct {
	double g;
	double start_t;
	double end_t;
	double delta_t;
	double l;
	double q;
	double F_D;
	double Omega_D;
	double theta_0;
	double omega_0;
	double tol;
	long nr_steps;
	int verbose;
	char * method;
} Params;

void initCL(Params *params);
void parseCL(Params *params, int *argc, char **argv[]);
void parseFileCL(Params *params, char *fileName);
void dumpCL(FILE *fp, char prefix[], Params *params);
void finalizeCL(Params *params);
void printHelpCL(FILE *fp);

#endif