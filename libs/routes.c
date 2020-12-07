#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "routes.h"

Route alloc_route();

Route r_north_bound_routes[4];
Route r_south_bound_routes[4];
Route r_east_bound_routes[4];
Route r_west_bound_routes[4];

Point **r_all_points;

/* generates the points in the xy coordinate
 * space, and adds them to r_all_points */
void r_generate_points()
{
    r_all_points = (Point **)malloc(sizeof(Point *) * TOTAL_POINTS);

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
    Route west_to_north = alloc_route();
    Route south_to_north = alloc_route();
    Route east_to_north = alloc_route();
    Route west_to_south = alloc_route();
    Route east_to_south = alloc_route();
    Route north_to_south = alloc_route();
    Route south_to_east = alloc_route();
    Route north_to_east = alloc_route(); /* dis work */
    Route west_to_east = alloc_route();
    Route north_to_west = alloc_route();
    Route east_to_west = alloc_route();
    Route south_to_west = alloc_route(); /* dis work */

    /* assign the names to each route */
    strcpy(west_to_north.name, "west_to_north");
    strcpy(south_to_north.name, "south_to_north");
    strcpy(east_to_north.name, "east_to_north");
    strcpy(west_to_south.name, "west_to_south");
    strcpy(east_to_south.name, "east_to_south");
    strcpy(north_to_south.name, "north_to_south");
    strcpy(south_to_east.name, "south_to_east");
    strcpy(north_to_east.name, "north_to_east");
    strcpy(west_to_east.name, "west_to_east");
    strcpy(north_to_west.name, "north_to_west");
    strcpy(east_to_west.name, "east_to_west");
    strcpy(south_to_west.name, "south_to_west");

    west_to_north.points[0] = r_all_points[6];
    west_to_north.points[1] = r_all_points[7];
    west_to_north.points[2] = r_all_points[4];
    west_to_north.points[3] = r_all_points[1];
    south_to_north.points[0] = r_all_points[11];
    south_to_north.points[1] = r_all_points[8];
    south_to_north.points[2] = r_all_points[1];
    south_to_north.points[3] = u_new_point(-1, -1);
    south_to_north.points[3]->init = 0;
    east_to_north.points[0] = r_all_points[5];
    east_to_north.points[1] = r_all_points[4];
    east_to_north.points[2] = r_all_points[1];
    east_to_north.points[3] = u_new_point(-1, -1);
    east_to_north.points[3]->init = 0;
    west_to_south.points[0] = r_all_points[6];
    west_to_south.points[1] = r_all_points[7];
    west_to_south.points[2] = r_all_points[10];
    west_to_south.points[3] = u_new_point(-1, -1);
    west_to_south.points[3]->init = 0;
    ;
    east_to_south.points[0] = r_all_points[5];
    east_to_south.points[1] = r_all_points[4];
    east_to_south.points[2] = r_all_points[7];
    east_to_south.points[3] = r_all_points[10];
    north_to_south.points[0] = r_all_points[0];
    north_to_south.points[1] = r_all_points[3];
    north_to_south.points[2] = r_all_points[10];
    north_to_south.points[3] = u_new_point(-1, -1);
    north_to_south.points[3]->init = 0;
    south_to_east.points[0] = r_all_points[11];
    south_to_east.points[1] = r_all_points[8];
    south_to_east.points[2] = r_all_points[9];
    south_to_east.points[3] = u_new_point(-1, -1);
    south_to_east.points[3]->init = 0;
    north_to_east.points[0] = r_all_points[0];
    north_to_east.points[1] = r_all_points[3];
    north_to_east.points[2] = r_all_points[8];
    north_to_east.points[3] = r_all_points[9];
    west_to_east.points[0] = r_all_points[6];
    west_to_east.points[1] = r_all_points[7];
    west_to_east.points[2] = r_all_points[9];
    west_to_east.points[3] = u_new_point(-1, -1);
    west_to_east.points[3]->init = 0;
    north_to_west.points[0] = r_all_points[0];
    north_to_west.points[1] = r_all_points[3];
    north_to_west.points[2] = r_all_points[2];
    north_to_west.points[3] = u_new_point(-1, -1);
    north_to_west.points[3]->init = 0;
    east_to_west.points[0] = r_all_points[5];
    east_to_west.points[1] = r_all_points[4];
    east_to_west.points[2] = r_all_points[2];
    east_to_west.points[3] = u_new_point(-1, -1);
    east_to_west.points[3]->init = 0;
    south_to_west.points[0] = r_all_points[11];
    south_to_west.points[1] = r_all_points[8];
    south_to_west.points[2] = r_all_points[3];
    south_to_west.points[3] = r_all_points[2];

    printf("assembled plain routes...\n");

    /* generate routes heading to north */
    r_north_bound_routes[0] = south_to_north;
    r_north_bound_routes[1] = east_to_north;
    r_north_bound_routes[2] = west_to_north; /*Cannot drive here*/

    /* generate routes heading to south */
    r_south_bound_routes[0] = north_to_south;
    r_south_bound_routes[1] = east_to_south;
    r_south_bound_routes[2] = west_to_south;

    /* generate routes heading to east */
    r_east_bound_routes[0] = north_to_east; /*Cannot drive here*/
    r_east_bound_routes[1] = south_to_east;
    r_east_bound_routes[2] = west_to_east;

    /* generate routes heading to west */
    r_west_bound_routes[0] = north_to_west; /*Cannot drive here*/
    r_west_bound_routes[1] = south_to_west;
    r_west_bound_routes[2] = east_to_west;
    printf("assembled routes...\n");
}

Route r_random_route()
{
    int i;
    i = rand() % 100 + 1;
    if (i <= 44) /*Traffic from south*/
    {
        i = rand() % 100 + 1;
        if (i <= 75)
        {
            return r_north_bound_routes[0];
        }
        if (i > 75 && i < 88)
        {
            return r_east_bound_routes[1];
        }
        return r_west_bound_routes[1];
    }
    if (i > 44 && i < 82) /*Traffic from south*/
    {
        return r_south_bound_routes[0];
    }
    if (i > 82 && i <= 92)
    {
        i = rand() % 100 + 1;
        if (i < 40)
        {
            return r_south_bound_routes[1];
        }
        if (i > 40 && i <= 80)
        {
            return r_north_bound_routes[1];
        }
        return r_west_bound_routes[2];
    }
    else
    {
        i = rand() % 100 + 1;
        if (i <= 90)
        {
            return r_south_bound_routes[2];
        }
        return r_east_bound_routes[2];
    }
}

/* TODO: find a better way  */
Point *r_point_by_index(uint i)
{
    switch (i)
    {
    case 0:
        return r_south_bound_routes[0].points[0];
        break;
    case 1:
        return r_north_bound_routes[0].points[2];
        break;
    case 2:
        return r_west_bound_routes[2].points[2];
        break;
    case 3:
        return r_east_bound_routes[0].points[1];
        break;
    case 4:
        return r_north_bound_routes[1].points[1];
        break;
    case 5:
        return r_north_bound_routes[1].points[0];
        break;
    case 6:
        return r_north_bound_routes[2].points[0];
        break;
    case 7:
        return r_south_bound_routes[2].points[1];
        break;
    case 8:
        return r_north_bound_routes[0].points[1];
        break;
    case 9:
        return r_east_bound_routes[1].points[2];
        break;
    case 10:
        return r_south_bound_routes[0].points[2];
        break;
    case 11:
        return r_north_bound_routes[0].points[0];
        break;
    default:
        return NULL;
        break;
    }
}

/* internal route allocation function */
Route alloc_route()
{
    return *(Route *)malloc(sizeof(Route));
}