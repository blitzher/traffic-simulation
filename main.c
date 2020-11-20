#include <stdio.h>
#include "utility.h"

int main(void)
{
    Point a = u_new_point(0, 0);
    Point b = u_new_point(100, 100);
    Car c = u_new_car(a, &b);

    printf("\nPoint a:\n");
    u_print_point(a);
    printf("\nPoint b:\n");
    u_print_point(b);
    printf("\nCar c:\n");
    u_print_car(c);

    printf("\nDistance between a and b: ");
    printf("%.10f\n", u_distance(a, b));
    return 0;
}
