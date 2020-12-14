#include <stdio.h>
#include <time.h>
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
    int msec;
    clock_t start, diff;

    srand(time(NULL));

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

    /* timing */
    start = clock();
    s_run_simulation(u_configs);
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;

    c_printf("simulation time: %ds %dms\n", GRN, msec/1000, msec%1000);

    u_compile_output(".output", argv[1]);

    c_printf("simulation terminated succesfully\n", BLU);


    return 0;
}
