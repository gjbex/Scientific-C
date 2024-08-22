#include <err.h>
#include <stdlib.h>

#include "particle.h"

static long id = 0;

Particle *initParticle(Params *params) {
    Particle *p = (Particle *) malloc(sizeof(Particle));
    if (p == NULL) {
        errx(EXIT_FAILURE, "can't allocate particle");
    }
    p->id = ++id;
    p->origin = 0;
    p->position = p->origin;
    return p;
}

void moveParticle(Particle *p, Params *params) {
    p->position += ((rand() % 2 == 1) ? +1 : -1);
}

void moveConfinedParticle(Particle *p, Params *params) {
    if (p->position == params->leftWall)
        p->position++;
    else if (p->position == params->rightWall)
        p->position--;
    else
        moveParticle(p, params);
}

void printParticle(FILE *fp, Particle *p, Params *params) {
    fprintf(fp, "particle %5d at %10ld (%10ld)\n", p->id,
            p->position, p->origin);
}

void freeParticle(Particle *p) {
    free(p);
}
