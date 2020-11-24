/* Traffic simulation program developed by
 * Group A404 at Aalborg University
 * October to December 2020 */
#include <stdio.h>
#include "routes.h"
#include "utility.h"

/* the main entry point of the program */
int main(void)
{

    /* load configs from .config file */
    u_load_configs(".config", &u_configs);

    /* generate points and routes */
    r_generate_points();
    r_generate_routes();

    /* assume that the entire simulation will be run
     * within a 100x100 grid */

    return 0;
}
