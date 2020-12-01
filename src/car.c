#include <stdio.h>
#include "../libs/routes.h"
#include "../libs/utility.h"
#include "../libs/colours.h"
#include "../libs/simulation.h"
int main(void)
{
    /*WIP.*/

    r_generate_points();
    r_generate_routes();

    u_load_configs(".config", &u_configs);

    s_run_simulation(u_configs);

    c_printf("simulation terminated succesfully\n", BLU);

    return 0;
}
