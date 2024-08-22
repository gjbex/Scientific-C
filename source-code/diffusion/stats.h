#ifndef HDR_STATS
#define HDR_STATS

#include <stdio.h>

typedef struct {
    long n;
    double sum, sum2;
    double min, max;
} Stats;

Stats *initStats(void);
void addData(Stats *stats, double value);
double getSum(Stats *stats);
double getSum2(Stats *stats);
double getMean(Stats *stats);
double getMean2(Stats *stats);
double getStddev(Stats *stats);
double getMin(Stats *stats);
double getMax(Stats *stats);
void printStats(FILE *fp, Stats *stats);
void freeStats(Stats *stats);

#endif
