#ifndef HDR_PARTICLE
#define HDR_PARTICLE

#include <stdio.h>
#include "cl_params.h"

typedef struct {
  int id;
  long origin;
  long position;
} Particle;

Particle *initParticle(Params *params);
void moveParticle(Particle *p, Params *params);
void moveConfinedParticle(Particle *p, Params *params);
void printParticle(FILE *fp, Particle *p, Params *params);
void freeParticle(Particle *p);

#endif
