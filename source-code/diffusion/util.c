#include <stdlib.h>
#include <time.h>

#include "util.h"

void seedRand(long seed) {
    if (seed < 0)
        srand(time(0)%RAND_MAX);
    else
        srand(seed);
}
