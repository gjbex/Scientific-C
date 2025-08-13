#include <stdio.h>

#define Point2d_struct struct { int x, y; }

typedef Point2d_struct Point2d;

typedef struct {
    Point2d_struct;
    int z;
} Point3d;

static void inline _print_point2d(Point2d p) {
    printf("(%d, %d)\n", p.x, p.y);
}
static void inline _print_point3d(Point3d p) {
    printf("(%d, %d, %d)\n", p.x, p.y, p.z);
}

#define print_point(p) \
    _Generic((p), \
        Point2d: _print_point2d, \
        Point3d: _print_point3d \
    )(p)

int main() {
    Point2d p2d = {1, 2};
    Point3d p3d = {3, 4, 5};

    print_point(p2d); // Output: (1, 2)
    print_point(p3d); // Output: (3, 4, 5)

    return 0;
}
