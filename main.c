#include <stdio.h>
#include "utility.h"

int main(void)
{

    Point a, b;
    Car c;

    /* load configs from .config file */
    u_load_configs(".config", &u_configs);
    u_print_configs(&u_configs);

    a = u_new_point(0, 0);
    b = u_new_point(100, 100);
    c = u_new_car(&a, &b);

    printf("\nPoint a:\n");
    u_print_point(&a);
    printf("\nPoint b:\n");
    u_print_point(&b);
    printf("\nCar c:\n");
    u_print_car(&c);

    printf("\nDistance between a and b: ");
    printf("%.10f\n", u_distance(a, b));
    return 0;
}
