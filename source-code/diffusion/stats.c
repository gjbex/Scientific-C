#include <err.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stats.h"

Stats *initStats(void) {
    Stats *stats = (Stats *) malloc(sizeof(Stats));
    if (stats == NULL)
        errx(EXIT_FAILURE, "can't allocate stats");
    stats->n = 0;
    stats->sum = stats->sum2 = 0.0;
    stats->min = DBL_MAX;
    stats->max = -DBL_MAX;
    return stats;
}

void addData(Stats *stats, double value) {
    stats->n++;
    stats->sum += value;
    stats->sum2 += value*value;
    if (value < stats->min)
        stats->min = value;
    if (value > stats->max)
        stats->max = value;
}

double getSum(Stats *stats) {
    if (stats->n < 1)
        errx(EXIT_FAILURE, "no data for statistics");
    return stats->sum;
}

double getSum2(Stats *stats) {
    if (stats->n < 1)
        errx(EXIT_FAILURE, "no data for statistics");
    return stats->sum2;
}

double getMean(Stats *stats) {
    if (stats->n < 1)
        errx(EXIT_FAILURE, "no data for statistics");
    return stats->sum/stats->n;
}

double getMean2(Stats *stats) {
    if (stats->n < 1)
        errx(EXIT_FAILURE, "no data for statistics");
    return stats->sum2/stats->n;
}

double getStddev(Stats *stats) {
    if (stats->n < 2)
        errx(EXIT_FAILURE, "no data for statistics");
    return sqrt((stats->sum2 - stats->sum*stats->sum/stats->n)/(stats->n - 1));
}

double getMin(Stats *stats) {
    if (stats->n < 1)
        errx(EXIT_FAILURE, "no data for statistics");
    return stats->min;
}

double getMax(Stats *stats) {
    if (stats->n < 1)
        errx(EXIT_FAILURE, "no data for statistics");
    return stats->max;
}

void printStats(FILE *fp, Stats *stats) {
    fprintf(fp, "n = %ld\n", stats->n);
    fprintf(fp, "sum = %le\n", stats->sum);
    fprintf(fp, "sum2 = %le\n", stats->sum2);
    fprintf(fp, "min = %le\n", stats->min);
    fprintf(fp, "max = %le\n", stats->max);
}

void freeStats(Stats *stats) {
    free(stats);
}
