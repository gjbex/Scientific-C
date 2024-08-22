#include <err.h>
#include <math.h>
#include <stdlib.h>

#include "distribution.h"

#define ABS(N) ((N) < 0 ? -(N) : (N))

Distribution *initDistribution(Params *params) {
    Distribution *distr = (Distribution *) malloc(sizeof(Distribution));
    if (distr == NULL)
        errx(EXIT_FAILURE, "can't allocate distribution");
    distr->size = 2*params->maxSteps + 1;
    distr->left = -params->maxSteps;
    distr->right = params->maxSteps;
    distr->occurrences = (long *) malloc(distr->size*sizeof(long));
    if (distr->occurrences == NULL)
        errx(EXIT_FAILURE, "can't allocate vector distribution");
    for (long pos = 0; pos < distr->size; pos++)
        distr->occurrences[pos] = 0;
    distr->min = distr->max = 0;
    return distr;
}

void addPosition(Distribution *distr, Particle *p) {
    distr->occurrences[p->position - distr->left]++;
    if (p->position < distr->min)
        distr->min = p->position;
    if (p->position > distr->max)
        distr->max = p->position;
}

Density *computeDensity(Distribution *distr) {
    Density *density = (Density *) malloc(sizeof(Density));
    if (density == NULL)
        errx(EXIT_FAILURE, "can't allocate density");
    density->min = distr->min;
    density->max = distr->max;
    density->left = distr->left;
    density->size = distr->size;
    density->rho = (double *) malloc(density->size*sizeof(double));
    if (density->rho == NULL)
        errx(EXIT_FAILURE, "can't allocate density values");
    double sum = 0.0;
    for (long k = 0; k < density->size; k++) {
        density->rho[k] = distr->occurrences[k];
        sum += distr->occurrences[k];
    }
    for (long k = 0; k < density->size; k++)
        density->rho[k] /= sum;
    return density;
}

void freeDensity(Density *density) {
    free(density->rho);
    free(density);
}

void printDensity(FILE *fp, Distribution *distr) {
    Density *density = computeDensity(distr);
    for (long k = density->min; k <= density->max; k++)
        fprintf(fp, "%-10ld %.6lf\n", k, density->rho[k - density->left]);
    freeDensity(density);
}

void printDistribution(FILE *fp, Distribution *distr, Params *params) {
    for (int position = distr->min; position <= distr->max; position++)
        fprintf(fp, "%-10d %-10ld\n",
                position, distr->occurrences[position - distr->left]);
}

void freeDistribution(Distribution *distr) {
    free(distr->occurrences);
    free(distr);
}

double computeEntropy(Distribution *distr, Params *params) {
    Density *density = computeDensity(distr);
    double entropy = 0.0;
    for (long k = 0; k < density->size; k++)
        if (density->rho[k] > 0.0)
            entropy += -density->rho[k]*log(density->rho[k]);
    freeDensity(density);
    return entropy;
}

DistributionList *initDistributionList(Params *params) {
    DistributionList *distrs;
    distrs = (DistributionList *) malloc(sizeof(DistributionList));
    if (distrs == NULL)
        errx(EXIT_FAILURE, "can't allocate distribution collection");
    distrs->nrDistrs  = 1 + params->maxSteps/params->deltaSteps;
    distrs->distr = (Distribution **) malloc(distrs->nrDistrs*
                                             sizeof(Distribution *));
    if (distrs->distr == NULL)
        errx(EXIT_FAILURE, "can't allocate distributions");
    for (int i = 0; i < distrs->nrDistrs; i++)
        distrs->distr[i] = initDistribution(params);
    return distrs;
}

void printDistributionList(FILE *fp, DistributionList *distrs,
                           Params *params) {
    fprintf(fp, "nr distributions: %ld\n", distrs->nrDistrs);
    for (long i = 0; i < distrs->nrDistrs; i++) {
        fprintf(fp, "# -----\n");
        printDistribution(fp, distrs->distr[i], params);
    }
}

void freeDistributionList(DistributionList *distrs) {
    for (long i = 0; i < distrs->nrDistrs; i++)
        freeDistribution(distrs->distr[i]);
    free(distrs->distr);
    free(distrs);
}
