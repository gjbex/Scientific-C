#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double g = 9.81;        /* m/s^2 */
const double v_0 = 700.0;     /* m/s */
const double delta_t = 0.005; /* s */
const double B2_m = 4e-5;     /* 1/m */

double position_x(double x_prev, double v_x, double delta_t);
double position_y(double y_prev, double v_y, double delta_t);
double velocity_x(double v_x_prev, double v_y_prev, double delta_t);
double velocity_y(double v_x_prev, double v_y_prev, double delta_t);
double energy(double y, double v_x, double v_y);

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
        double v_x_new, v_y_new;
        double E = energy(y, v_x, v_y);
        printf("%.5f %.5f %.5f %.5f %.5f %.5f\n", t, x, y, v_x, v_y, E);
        v_x_new = velocity_x(v_x, v_y, delta_t);
        v_y_new = velocity_y(v_x, v_y, delta_t);
        x = position_x(x, 0.5*(v_x_new + v_x), delta_t);
        y = position_y(y, 0.5*(v_y_new + v_y), delta_t);
        v_x = v_x_new;
        v_y = v_y_new;
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

double velocity_x(double v_x_prev, double v_y_prev, double delta_t) {
    double v = sqrt(v_x_prev*v_x_prev + v_y_prev*v_y_prev);
    return v_x_prev - B2_m*v*v_x_prev*delta_t;
}

double velocity_y(double v_x_prev, double v_y_prev, double delta_t) {
    double v = sqrt(v_x_prev*v_x_prev + v_y_prev*v_y_prev);
    return v_y_prev - g*delta_t - B2_m*v*v_y_prev*delta_t;
}

double energy(double y, double v_x, double v_y) {
    return y*g + (v_x*v_x + v_y*v_y)/2.0;
}
