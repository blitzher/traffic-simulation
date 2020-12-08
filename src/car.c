#include <stdio.h>
#include "../libs/utility.h"
#include "../libs/routes.h"
#include "../libs/colours.h"
#include "../libs/simulation.h"

/* 
 * argc: argument count
 * argv: argument values
 */

int main(int argc, char **argv)
{
    srand(time(NULL));
    /*WIP.*/

    r_generate_points();
    r_generate_routes();

    if (argc > 1)
    {
        u_load_configs(argv[1], &u_configs);
    }
    else
    {
        u_load_configs(".config", &u_configs);
    }

    s_run_simulation(u_configs);

    u_compile_output(".output", argv[1]);

    c_printf("simulation terminated succesfully\n", BLU);

    return 0;
}
