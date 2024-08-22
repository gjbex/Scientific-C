#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cl_params.h"

typedef struct {
    double t;
    double theta;
    double omega;
} Vars;

void euler(Vars *vars, Params *params);
void euler_cromer(Vars *vars, Params *params);
void printData(Vars vars);

int main(int argc, char *argv[]) {
    Params params;
    Vars vars;
    void (*method)(Vars *, Params *);
    double t;
    initCL(&params);
    if (argc > 1)
        if (access(argv[1], R_OK) != -1) {
            parseFileCL(&params, argv[1]);
            argc++;
            argv += 1;
        }
    parseCL(&params, &argc, &argv);
    if (params.verbose)
        dumpCL(stderr, "# ", &params);
    if (strcmp(params.method, "euler") == 0)
        method = euler;
    else if (strcmp(params.method, "euler_cromer") == 0)
        method = euler_cromer;
    else
        errx(EXIT_FAILURE, "unknown integration method %s", params.method);
    vars.theta = params.theta_0;
    vars.omega = params.omega_0;
    vars.t     = params.start_t;

    printf("# time theta omega\n");
    printData(vars);
    for (t = params.start_t; t <= params.end_t; t += params.delta_t) {
        method(&vars, &params);
        printData(vars);
    }

    finalizeCL(&params);
    return EXIT_SUCCESS;
}

void euler(Vars *vars, Params *params) {
    double new_theta, new_omega;
    new_omega = vars->omega + (
            -params->g*vars->theta/params->l
            - params->q*vars->omega
            + params->F_D*sin(params->Omega_D*vars->t)
    )*params->delta_t;
    new_theta = vars->theta + vars->omega*params->delta_t;
    vars->theta = new_theta;
    vars->omega = new_omega;
    vars->t += params->delta_t;
}

void euler_cromer(Vars *vars, Params *params) {
    double new_theta, new_omega;
    new_omega = vars->omega + (
            -params->g*vars->theta/params->l
            - params->q*vars->omega
            + params->F_D*sin(params->Omega_D*vars->t)
    )*params->delta_t;
    new_theta = vars->theta + new_omega*params->delta_t;
    vars->theta = new_theta;
    vars->omega = new_omega;
    vars->t += params->delta_t;
}

void printData(Vars vars) {
    printf("%.12e % 12e %.12e\n", vars.t, vars.theta, vars.omega);
}
