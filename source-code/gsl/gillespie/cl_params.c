#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "cl_params.h"
#include "cl_params_aux.h"

#define MAX_CL_OPT_LEN 128
#define MAX_CL_LINE_LEN 1024

void initCL(Params *params) {
	params->n_a = 1.0e3;
	params->n_b = 1.0e3;
	params->n_ab = 0.0;
	params->k_B = 1.0;
	params->k_D = 2.0;
	params->t_max = 0.05;
	params->verbose = 0;
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
		if (!strncmp((*argv)[i], "-n_a", 5)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-n_a' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->n_a = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-n_b", 5)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-n_b' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->n_b = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-n_ab", 6)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-n_ab' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->n_ab = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-k_B", 5)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-k_B' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->k_B = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-k_D", 5)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-k_D' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->k_D = atof(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-t_max", 7)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-t_max' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->t_max = atof(argv_str);
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
		if (sscanf(line_str, "n_a = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-n_a' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->n_a = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "n_b = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-n_b' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->n_b = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "n_ab = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-n_ab' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->n_ab = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "k_B = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-k_B' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->k_B = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "k_D = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-k_D' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->k_D = atof(argv_str);
			continue;
		}
		if (sscanf(line_str, "t_max = %[^\n]", argv_str) == 1) {
			if (!isDoubleCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-t_max' of type double\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->t_max = atof(argv_str);
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
		fprintf(stderr, "### warning, line can not be parsed: '%s'\n", line_str);
	}
	fclose(fp);
}

void dumpCL(FILE *fp, char prefix[], Params *params) {
	fprintf(fp, "%sn_a = %.16lf\n", prefix, params->n_a);
	fprintf(fp, "%sn_b = %.16lf\n", prefix, params->n_b);
	fprintf(fp, "%sn_ab = %.16lf\n", prefix, params->n_ab);
	fprintf(fp, "%sk_B = %.16lf\n", prefix, params->k_B);
	fprintf(fp, "%sk_D = %.16lf\n", prefix, params->k_D);
	fprintf(fp, "%st_max = %.16lf\n", prefix, params->t_max);
	fprintf(fp, "%sverbose = %d\n", prefix, params->verbose);
}

void finalizeCL(Params *params) {
}

void printHelpCL(FILE *fp) {
	fprintf(fp, "  -n_a <DP float>\n  -n_b <DP float>\n  -n_ab <DP float>\n  -k_B <DP float>\n  -k_D <DP float>\n  -t_max <DP float>\n  -verbose <integer>\n  -?: print this message");
}