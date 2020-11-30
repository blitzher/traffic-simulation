#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include "routes.h"

Point *alloc_route(utiny_i size);

Point *r_north_bound_routes[4];
Point *r_south_bound_routes[4];
Point *r_east_bound_routes[4];
Point *r_west_bound_routes[4];

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

/* TODO: find a better way to do this */
void r_generate_routes()
{
    /* thanks to Peter Frandsen, for debugging this
     * PoS code :) */
    Point *west_to_north = alloc_route(4);
    Point *south_to_north = alloc_route(4);
    Point *east_to_north = alloc_route(4);
    Point *west_to_south = alloc_route(4);
    Point *east_to_south = alloc_route(4);
    Point *north_to_south = alloc_route(4);
    Point *south_to_east = alloc_route(4);
    Point *north_to_east = alloc_route(4);
    Point *west_to_east = alloc_route(4);
    Point *north_to_west = alloc_route(4);
    Point *east_to_west = alloc_route(4);
    Point *south_to_west = alloc_route(4);

    west_to_north[0] = r_all_points[6];
    west_to_north[1] = r_all_points[7];
    west_to_north[2] = r_all_points[4];
    west_to_north[3] = r_all_points[1];
    south_to_north[0] = r_all_points[11];
    south_to_north[1] = r_all_points[8];
    south_to_north[2] = r_all_points[1];
    east_to_north[0] = r_all_points[5];
    east_to_north[1] = r_all_points[4];
    east_to_north[2] = r_all_points[1];
    west_to_south[0] = r_all_points[6];
    west_to_south[1] = r_all_points[7];
    west_to_south[2] = r_all_points[10];
    east_to_south[0] = r_all_points[5];
    east_to_south[1] = r_all_points[4];
    east_to_south[2] = r_all_points[7];
    east_to_south[3] = r_all_points[10];
    north_to_south[0] = r_all_points[0];
    north_to_south[1] = r_all_points[3];
    north_to_south[2] = r_all_points[10];
    south_to_east[0] = r_all_points[11];
    south_to_east[1] = r_all_points[8];
    south_to_east[2] = r_all_points[9];
    north_to_east[0] = r_all_points[0];
    north_to_east[1] = r_all_points[3];
    north_to_east[2] = r_all_points[8];
    north_to_east[3] = r_all_points[9];
    west_to_east[0] = r_all_points[6];
    west_to_east[1] = r_all_points[7];
    west_to_east[2] = r_all_points[9];
    north_to_west[0] = r_all_points[0];
    north_to_west[1] = r_all_points[3];
    north_to_west[2] = r_all_points[2];
    east_to_west[0] = r_all_points[5];
    east_to_west[1] = r_all_points[4];
    east_to_west[2] = r_all_points[2];
    south_to_west[0] = r_all_points[11];
    south_to_west[1] = r_all_points[8];
    south_to_west[2] = r_all_points[3];
    south_to_west[3] = r_all_points[2];

    printf("assembled plain routes...\n");

    /* generate routes heading to north */
    r_north_bound_routes[0] = south_to_north;
    r_north_bound_routes[1] = east_to_north;
    r_north_bound_routes[2] = west_to_north;

    /* generate routes heading to south */
    r_south_bound_routes[0] = north_to_south;
    r_south_bound_routes[1] = east_to_south;
    r_south_bound_routes[2] = west_to_south;

    /* generate routes heading to east */
    r_east_bound_routes[0] = north_to_east;
    r_east_bound_routes[1] = south_to_east;
    r_east_bound_routes[2] = west_to_east;

    /* generate routes heading to west */
    r_west_bound_routes[0] = north_to_west;
    r_west_bound_routes[1] = south_to_west;
    r_west_bound_routes[2] = east_to_west;
    printf("assembled routes...\n");
}

/* internal route allocation function */
Point *alloc_route(utiny_i size)
{
    return (Point *)malloc(sizeof(Point) * size);
}