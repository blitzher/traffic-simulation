/* different utility library, related primarily
 * to the generation, and computations regarding
 * the routes, and their abstraction
 * note that all functions and variables defined
 * are prefixed by 'r_' */
#pragma once

#include "utility.h"

/* define symbolic constants
 * related to the generation of routes */
#define TOTAL_POINTS 12
#define TOTAL_ROUTES 12
#define MAX_ROUTE_LEN 4

void r_generate_points();
void r_generate_routes();

/*
 *      0 1
 * 
 * 2    3 4     5
 * 6    7 8     9
 *  
 *     10 11
 * */

/* collection of all points, 
 * sorted from top left to bottom right */
Point r_all_points[TOTAL_POINTS];

/* collections of each route heading north */
Point *r_north_bound_routes[MAX_ROUTE_LEN];
/* collections of each route heading south */
Point *r_south_bound_routes[MAX_ROUTE_LEN];
/* collections of each route heading east */
Point *r_east_bound_routes[MAX_ROUTE_LEN];
/* collections of each route heading west */
Point *r_west_bound_routes[MAX_ROUTE_LEN];

/* pick a random route among all, unbiased */
Point *r_random_route();

/* get a point by its (i, j) index */
Point r_point_by_index(uint i);