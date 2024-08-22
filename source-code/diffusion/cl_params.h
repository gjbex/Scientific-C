#ifndef CL_PARAMS_HDR
#define CL_PARAMS_HDR

#include <stdio.h>

typedef struct {
	long maxSteps;
	long deltaSteps;
	long leftWall;
	long rightWall;
	long nrParticles;
	int constrained;
	int verbose;
	long seed;
} Params;

void initCL(Params *params);
void parseCL(Params *params, int *argc, char **argv[]);
void parseFileCL(Params *params, char *fileName);
void dumpCL(FILE *fp, char prefix[], Params *params);
void finalizeCL(Params *params);
void printHelpCL(FILE *fp);

#endif