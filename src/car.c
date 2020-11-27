#include <stdio.h>
#include "../libs/routes.h"
#include "../libs/utility.h"
#include "../libs/colours.h"
int main(void)
{
    /*WIP.*/
    r_generate_points();
    r_generate_routes();
    u_print_route(r_south_bound_routes[0]);
    printf("succcccccccc");

    return 0;
}
