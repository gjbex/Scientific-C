#ifndef HDR_DISTRIBUTION
#define HDR_DISTRIBUTION

#include <stdio.h>
#include "cl_params.h"
#include "particle.h"

typedef struct {
    long *occurrences;
    long size, left, right, min, max;
} Distribution;

typedef struct {
    Distribution **distr;
    long nrDistrs;
} DistributionList;

typedef struct {
    double *rho;
    long size, min, max, left;
} Density;

Distribution *initDistribution(Params *params);
void addPosition(Distribution *distr, Particle *p);
void printDistribution(FILE *fp, Distribution *distr, Params *params);
void freeDistribution(Distribution *distr);

void printDensity(FILE *fp, Distribution *distr);

double computeEntropy(Distribution *distr, Params *params);

DistributionList *initDistributionList(Params *params);
void printDistributionList(FILE *fp, DistributionList *distrs,
                           Params *params);
void freeDistributionList(DistributionList *distrs);

#endif
