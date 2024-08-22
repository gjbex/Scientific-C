#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "cl_params.h"
#include "particle.h"
#include "distribution.h"
#include "stats.h"
#include "util.h"

int main(int argc, char *argv[]) {
    if (argc != 2)
        errx(EXIT_FAILURE, "parameter file expected");
    Params params;
    initCL(&params);
    parseFileCL(&params, argv[1]);
    dumpCL(stdout, "# ", &params);
    seedRand(params.seed);
    void (*move)(Particle *, Params *) =
        params.constrained ? moveConfinedParticle : moveParticle;
    Distribution *distr = initDistribution(&params);
    Stats *stats = initStats();
    for (long n = 0; n < params.nrParticles; n++) {
        int init_step = n % 2;
        if (params.verbose)
            fprintf(stderr, "### msg: particle %ld\n", n);
        Particle *p = initParticle(&params);
        for (int step = init_step; step < params.maxSteps; step++) {
            if (params.verbose)
                fprintf(stderr, "### msg: particle %ld, step %d\n",
                        n, step);
            move(p, &params);
        }
        addPosition(distr, p);
        addData(stats, p->position);
        freeParticle(p);
    }
    fprintf(stdout, "# %ld %.3lf %.3lf\n",
            params.maxSteps, getMean(stats), getMean2(stats));
    fprintf(stdout, "# %ld %.3lf %.3lf\n",
            params.maxSteps, getMean(stats), getStddev(stats));
    printDensity(stdout, distr);
    freeDistribution(distr);
    freeStats(stats);
    finalizeCL(&params);
    return EXIT_SUCCESS;
}
