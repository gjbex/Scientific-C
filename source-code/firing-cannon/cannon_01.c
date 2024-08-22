#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double g = 9.81;        /* m/s^2 */
const double v_0 = 700.0;     /* m/s */
const double delta_t = 0.005; /* s */

double position_x(double t, double alpha);
double position_y(double t, double alpha);
double velocity_y(double t, double alpha);

int main(int argc, char *argv[]) {
    double alpha, t, x, y, v_x, v_y, x_max_y, max_y;
    if (argc != 2) {
        errx(EXIT_FAILURE, "Expecting launch angle");
    }
    alpha = strtod(argv[1], NULL);
    x = 0.0;
    y = 0.0;
    v_x = v_0*cos(alpha);
    v_y = v_0*sin(alpha);
    t = 0.0;
    x_max_y = 0.0;
    max_y = 0.0;
    while (y >= 0.0) {
        printf("%.5f %.5f %.5f %.5f %.5f\n", t, x, y, v_x, v_y);
        t += delta_t;
        x = position_x(t, alpha);
        y = position_y(t, alpha);
        v_y = velocity_y(t, alpha);
        if (y > max_y) {
            max_y = y;
            x_max_y = x;
        }
    }
    printf("# max. altitude %.5f at %.5f\n", max_y, x_max_y);
    return EXIT_SUCCESS;
}

double position_x(double t, double alpha) {
    return v_0*cos(alpha)*t;
}

double position_y(double t, double alpha) {
    return v_0*sin(alpha)*t - g*t*t/2.0;
}

double velocity_y(double t, double alpha) {
    return v_0*sin(alpha) - g*t;
}
