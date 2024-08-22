#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Circle {
    double x, y, r;
};

double area(struct Circle circle);
bool have_overlap(struct Circle circle_1, struct Circle circle_2);
void scale(struct Circle circle, double factor);
void print_circle(struct Circle circle);

int main(void) {
    struct Circle circle_1, circle_2, circle_3;
    circle_1.x = 1.0;
    circle_1.y = -1.0;
    circle_1.r = 2.0;
    circle_2.x = -1.0;
    circle_2.y = 1.0;
    circle_2.r = 1.5;
    circle_3.x = -10.0;
    circle_3.y = 10.0;
    circle_3.r = 0.5;
    printf("circle 1: "); print_circle(circle_1);
    printf("circle 2: "); print_circle(circle_2);
    printf("circle 3: "); print_circle(circle_3);
    printf("circle 1 area = %lf\n", area(circle_1));
    printf("circle 2 area = %lf\n", area(circle_2));
    if (have_overlap(circle_1, circle_2)) {
        printf("circles 1 and 2 overlap\n");
    } else {
        printf("circles 1 and 2 don't overlap\n");
    }
    if (have_overlap(circle_1, circle_3)) {
        printf("circles 1 and 3 overlap\n");
    } else {
        printf("circles 1 and 3 don't overlap\n");
    }
    printf("circle 1: "); print_circle(circle_1);
    printf("circle 2: "); print_circle(circle_2);
    scale(circle_1, 2.0);
    printf("scaled circle 1: "); print_circle(circle_1);
    return EXIT_SUCCESS;
}

double area(struct Circle circle) {
    const double pi = 3.14159265359;
    return pi*circle.r*circle.r;
}

bool have_overlap(struct Circle c1, struct Circle c2) {
    double distance = sqrt((c1.x - c2.x)*(c1.x - c2.x) +
                           (c1.y - c2.y)*(c1.y - c2.y));
    return c1.r + c2.r >= distance;
}

void print_circle(struct Circle circle) {
    printf("(%lf, %lf): %lf\n", circle.x, circle.y, circle.r);
}

/*
   This function will not work as (perhaps) expected, this is call by
   value semantics.
*/
void scale(struct Circle circle, double factor) {
    circle.r *= factor;
}
