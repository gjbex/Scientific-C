#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "cl_params.h"
#include "cl_params_aux.h"

#define MAX_CL_OPT_LEN 128
#define MAX_CL_LINE_LEN 1024

void initCL(Params *params) {
	params->g = 9.81;
	params->start_t = 0.0;
	params->end_t = 20.0;
	params->delta_t = 0.005;
	params->l = 1.0;
	params->q = 0.0;
	params->F_D = 0.0;
	params->Omega_D = 2.0;
	params->theta_0 = 0.1;
	params->omega_0 = 0.0;
	params->tol = 1.0e-8;
	params->nr_steps = 10000;
	params->verbose = 1;
	int len;
	len = strlen("euler");
	if (!(params->method = (char *) calloc(len + 1, sizeof(char))))
		errx(EXIT_CL_ALLOC_FAIL, "can not allocate method field");
	strncpy(params->method, "euler", len + 1);
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
		if (!strncmp((*argv)[i], "-g", 3)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-g' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->g = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-start_t", 9)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-start_t' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->start_t = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-end_t", 7)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-end_t' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->end_t = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-delta_t", 9)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-delta_t' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->delta_t = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-l", 3)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-l' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->l = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-q", 3)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-q' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->q = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-F_D", 5)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-F_D' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->F_D = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-Omega_D", 9)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-Omega_D' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->Omega_D = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-theta_0", 9)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-theta_0' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->theta_0 = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-omega_0", 9)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-omega_0' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->omega_0 = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-tol", 5)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-tol' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->tol = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-nr_steps", 10)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-nr_steps' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->nr_steps = atol(argv_str);
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
		if (!strncmp((*argv)[i], "-method", 8)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!1) {
				fprintf(stderr, "### error: invalid value for option '-method' of type char *\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			char *tmp;
			int len = strlen(argv_str);
			free(params->method);
			if (!(tmp = (char *) calloc(len + 1, sizeof(char))))
				errx(EXIT_CL_ALLOC_FAIL, "can not allocate char* field");
			params->method = strncpy(tmp, argv_str, len + 1);
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
		if (sscanf(line_str, "g = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-g' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->g = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "start_t = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-start_t' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->start_t = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "end_t = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-end_t' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->end_t = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "delta_t = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-delta_t' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->delta_t = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "l = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-l' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->l = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "q = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-q' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->q = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "F_D = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-F_D' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->F_D = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "Omega_D = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-Omega_D' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->Omega_D = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "theta_0 = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-theta_0' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->theta_0 = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "omega_0 = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-omega_0' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->omega_0 = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "tol = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-tol' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->tol = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "nr_steps = %[^\n]", argv_str) == 1) {
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-nr_steps' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->nr_steps = atol(argv_str);
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
		if (sscanf(line_str, "method = %[^\n]", argv_str) == 1) {
			if (!1) {
				fprintf(stderr, "### error: invalid value for option '-method' of type char *\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			char *tmp;
			int len = strlen(argv_str);
			free(params->method);
			if (!(tmp = (char *) calloc(len + 1, sizeof(char))))
				errx(EXIT_CL_ALLOC_FAIL, "can not allocate char* field");
			params->method = strncpy(tmp, argv_str, len + 1);
			stripQuotesCL(params->method);
			continue;
		}
		fprintf(stderr, "### warning, line can not be parsed: '%s'\n", line_str);
	}
	fclose(fp);
}

void dumpCL(FILE *fp, char prefix[], Params *params) {
	fprintf(fp, "%sg = %.16lf\n", prefix, params->g);
	fprintf(fp, "%sstart_t = %.16lf\n", prefix, params->start_t);
	fprintf(fp, "%send_t = %.16lf\n", prefix, params->end_t);
	fprintf(fp, "%sdelta_t = %.16lf\n", prefix, params->delta_t);
	fprintf(fp, "%sl = %.16lf\n", prefix, params->l);
	fprintf(fp, "%sq = %.16lf\n", prefix, params->q);
	fprintf(fp, "%sF_D = %.16lf\n", prefix, params->F_D);
	fprintf(fp, "%sOmega_D = %.16lf\n", prefix, params->Omega_D);
	fprintf(fp, "%stheta_0 = %.16lf\n", prefix, params->theta_0);
	fprintf(fp, "%somega_0 = %.16lf\n", prefix, params->omega_0);
	fprintf(fp, "%stol = %.16lf\n", prefix, params->tol);
	fprintf(fp, "%snr_steps = %ld\n", prefix, params->nr_steps);
	fprintf(fp, "%sverbose = %d\n", prefix, params->verbose);
	fprintf(fp, "%smethod = '%s'\n", prefix, params->method);
}

void finalizeCL(Params *params) {
	free(params->method);
}

void printHelpCL(FILE *fp) {
	fprintf(fp, "  -g <DP float>\n  -start_t <DP float>\n  -end_t <DP float>\n  -delta_t <DP float>\n  -l <DP float>\n  -q <DP float>\n  -F_D <DP float>\n  -Omega_D <DP float>\n  -theta_0 <DP float>\n  -omega_0 <DP float>\n  -tol <DP float>\n  -nr_steps <long integer>\n  -verbose <integer>\n  -method <string>\n  -?: print this message");
}