#include "utility.h"
#include "routes.h"

/* generates the points in the xy coordinate
 * space, and adds them to r_all_points */
void r_generate_points()
{
    r_all_points[0] = u_new_point(40, 0);
    r_all_points[1] = u_new_point(60, 0);
    r_all_points[2] = u_new_point(0, 40);
    r_all_points[3] = u_new_point(40, 40);
    r_all_points[4] = u_new_point(60, 40);
    r_all_points[5] = u_new_point(100, 40);
    r_all_points[6] = u_new_point(0, 60);
    r_all_points[7] = u_new_point(40, 60);
    r_all_points[8] = u_new_point(60, 60);
    r_all_points[9] = u_new_point(100, 60);
    r_all_points[10] = u_new_point(40, 100);
    r_all_points[11] = u_new_point(60, 100);
}

void r_generate_routes()
{
    int i;
    Point route[MAX_ROUTE_LEN];
    /* check if all points in r_all_points are
     * properly initialised */
    for (i = 0; i < TOTAL_POINTS; i++)
    {
        if (!r_all_points[i].init)
        {
            return;
        }
    }

    /* generate routes originating from north */
    route[0] = r_all_points[0], r_all_points[3], r_all_points[2];
}
