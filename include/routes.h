/* different utility library, related primarily
 * to the generation, and computations regarding
 * the routes, and their abstraction
 * note that all functions and variables defined
 * are prefixed by 'r_' */
#pragma once


/* define symbolic constants
 * related to the generation of routes */
#define TOTAL_POINTS 12
#define TOTAL_ROUTES 12
#define MAX_ROUTE_LEN 4
#define POINT_RADIUS 7 /* 7 because it is half of the speed of the car */

/* a route is primarily
 * an array of points */
typedef struct Route {
    Point* points[MAX_ROUTE_LEN];
    utiny_i length;
    char name[20];
} Route;

enum lights {red, green};

#include "utility.h"

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
Point **r_all_points;

/* collections of each route heading north */
Route r_north_bound_routes[4];
/* collections of each route heading south */
Route r_south_bound_routes[4];
/* collections of each route heading east */
Route r_east_bound_routes[4];
/* collections of each route heading west */
Route r_west_bound_routes[4];

/* pick a random route among all, unbiased */
Route r_random_route();

/* get a point by its (i, j) index */
Point *r_point_by_index(uint i);