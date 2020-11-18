#include <stdio.h>
#include <math.h>
#include "utility.h"

/* math helper functions */
double u_distance(Point a, Point b)
{
    return sqrt(u_distance_sqr(a, b));
}

double u_distance_sqr(Point a, Point b)
{
    double dist_sqr = pow(b.y - a.y, 2) + pow(b.x - a.x, 2);
    return dist_sqr;
}

/* struct initialization functions */
Point u_new_point(uint x, uint y)
{
    Point p;
    p.x = x;
    p.y = y;
    p.wait_points = 0;
    p.visits = 0;
    return p;
}

Car u_new_car(Point start, Point *goals)
{
    Car c;
    c.position = start;
    c.goals = goals;
    c.goal_index = 0;
    /* todo: add support for loading default values from config */
    return c;
}

/* print helper functions */
void u_print_point(Point p)
{
    printf("< x: %d, y: %d\n", p.x, p.y);
    printf("  wait_points: %d, visits: %d >\n", p.wait_points, p.visits);
}

void u_print_car(Car c)
{
    printf("Position:\n");
    u_print_point(c.position);
    printf("Current goal:\n");
    u_print_point(c.goals[0]);
}