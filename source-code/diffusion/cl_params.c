#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "cl_params.h"
#include "cl_params_aux.h"

#define MAX_CL_OPT_LEN 128
#define MAX_CL_LINE_LEN 1024

void initCL(Params *params) {
	params->maxSteps = 100;
	params->deltaSteps = 5;
	params->leftWall = -30;
	params->rightWall = 30;
	params->nrParticles = 10;
	params->constrained = 0;
	params->verbose = 0;
	params->seed = -1;
}

void parseCL(Params *params, int *argc, char **argv[]) {
	char *argv_str;
	int i = 1;
	while (i < *argc) {
		 if (!strncmp((*argv)[i], "-?", 3)) {
			printHelpCL(stderr);
			finalizeCL(params);
			exit(EXIT_SUCCESS);
		}
		if (!strncmp((*argv)[i], "-maxSteps", 10)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-maxSteps' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->maxSteps = atol(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-deltaSteps", 12)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-deltaSteps' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->deltaSteps = atol(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-leftWall", 10)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-leftWall' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->leftWall = atol(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-rightWall", 11)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-rightWall' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->rightWall = atol(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-nrParticles", 13)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-nrParticles' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->nrParticles = atol(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-constrained", 13)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-constrained' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->constrained = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-verbose", 9)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-verbose' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->verbose = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-seed", 6)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-seed' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->seed = atol(argv_str);
			i++;
			continue;
		}
		break;
	}
	if (i > 1) {
		(*argv)[i - 1] = (*argv)[0];
		*argv = &((*argv)[i - 1]);
		*argc -= (i - 1);
	}
}

void parseFileCL(Params *params, char *fileName) {
	char line_str[MAX_CL_LINE_LEN];
	char argv_str[MAX_CL_LINE_LEN];
	FILE *fp;
	if (!(fp = fopen(fileName, "r"))) {
		fprintf(stderr, "### error: can not open file '%s'\n", fileName);
		exit(EXIT_CL_FILE_OPEN_FAIL);
	}
	while (fgets(line_str, MAX_CL_LINE_LEN, fp)) {
		if (isCommentCL(line_str)) continue;
		if (isEmptyLineCL(line_str)) continue;
		if (sscanf(line_str, "maxSteps = %[^\n]", argv_str) == 1) {
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-maxSteps' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->maxSteps = atol(argv_str);
			continue;
		}
		if (sscanf(line_str, "deltaSteps = %[^\n]", argv_str) == 1) {
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-deltaSteps' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->deltaSteps = atol(argv_str);
			continue;
		}
		if (sscanf(line_str, "leftWall = %[^\n]", argv_str) == 1) {
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-leftWall' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->leftWall = atol(argv_str);
			continue;
		}
		if (sscanf(line_str, "rightWall = %[^\n]", argv_str) == 1) {
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-rightWall' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->rightWall = atol(argv_str);
			continue;
		}
		if (sscanf(line_str, "nrParticles = %[^\n]", argv_str) == 1) {
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-nrParticles' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->nrParticles = atol(argv_str);
			continue;
		}
		if (sscanf(line_str, "constrained = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-constrained' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->constrained = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "verbose = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-verbose' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->verbose = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "seed = %[^\n]", argv_str) == 1) {
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-seed' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->seed = atol(argv_str);
			continue;
		}
		fprintf(stderr, "### warning, line can not be parsed: '%s'\n", line_str);
	}
	fclose(fp);
}

void dumpCL(FILE *fp, char prefix[], Params *params) {
	fprintf(fp, "%smaxSteps = %ld\n", prefix, params->maxSteps);
	fprintf(fp, "%sdeltaSteps = %ld\n", prefix, params->deltaSteps);
	fprintf(fp, "%sleftWall = %ld\n", prefix, params->leftWall);
	fprintf(fp, "%srightWall = %ld\n", prefix, params->rightWall);
	fprintf(fp, "%snrParticles = %ld\n", prefix, params->nrParticles);
	fprintf(fp, "%sconstrained = %d\n", prefix, params->constrained);
	fprintf(fp, "%sverbose = %d\n", prefix, params->verbose);
	fprintf(fp, "%sseed = %ld\n", prefix, params->seed);
}

void finalizeCL(Params *params) {
}

void printHelpCL(FILE *fp) {
	fprintf(fp, "  -maxSteps <long integer>\n  -deltaSteps <long integer>\n  -leftWall <long integer>\n  -rightWall <long integer>\n  -nrParticles <long integer>\n  -constrained <integer>\n  -verbose <integer>\n  -seed <long integer>\n  -?: print this message");
}