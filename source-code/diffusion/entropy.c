#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "cl_params.h"
#include "particle.h"
#include "distribution.h"
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
    DistributionList *distrs = initDistributionList(&params);
    for (long n = 0; n < params.nrParticles; n++) {
        Particle *p = initParticle(&params);
        long distrNr = 0;
        addPosition(distrs->distr[distrNr], p);
        for (int step = 1; step <= params.maxSteps; step++) {
            move(p, &params);
            if (step % params.deltaSteps == 0) {
                long distrNr = step/params.deltaSteps;
                addPosition(distrs->distr[distrNr], p);
            }
        }
        freeParticle(p);
    }
    for (long k = 0; k < distrs->nrDistrs; k++)
        fprintf(stdout, "%-10ld %.6lf\n",
                k*params.deltaSteps, computeEntropy(distrs->distr[k],
                                                    &params));
    freeDistributionList(distrs);
    finalizeCL(&params);
    return EXIT_SUCCESS;
}
