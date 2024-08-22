#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double g = 9.81;        /* m/s^2 */
const double v_0 = 700.0;     /* m/s */
const double delta_t = 0.005; /* s */

double position_x(double x_prev, double v_x, double delta_t);
double position_y(double y_prev, double v_y, double delta_t);
double velocity_y(double v_y_prev, double delta_t);

int main(int argc, char *argv[]) {
    double alpha, t, x, y, v_x, v_y, x_max_y, max_y;
    if (argc != 2) {
        errx(EXIT_FAILURE, "Expecting launch angle");
    }
    alpha = strtod(argv[1], NULL);
    t = 0.0;
    x = 0.0;
    y = 0.0;
    v_x = v_0*cos(alpha);
    v_y = v_0*sin(alpha);
    x_max_y = 0.0;
    max_y = 0.0;
    while (y >= 0.0) {
        printf("%.5f %.5f %.5f %.5f %.5f\n", t, x, y, v_x, v_y);
        x = position_x(x, v_x, delta_t);
        y = position_y(y, v_y, delta_t);
        v_y = velocity_y(v_y, delta_t);
        t += delta_t;
        if (y > max_y) {
            x_max_y = x;
            max_y = y;
        }
    }
    printf("# max. altitude %.5f at %.5f\n", max_y, x_max_y);
    return EXIT_SUCCESS;
}

double position_x(double x_prev, double v_x, double delta_t) {
    return x_prev + v_x*delta_t;
}

double position_y(double y_prev, double v_y, double delta_t) {
    return y_prev + v_y*delta_t;
}

double velocity_y(double v_y_prev, double delta_t) {
    return v_y_prev - g*delta_t;
}
