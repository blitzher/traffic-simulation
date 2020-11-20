#pragma once

typedef unsigned int uint;
typedef unsigned short ushort;

/* arbitrary definition of maximum amount of goals */
#define MAX_GOALS 10;

/* abstract class for a point
 * to get a new point, use u_new_point */
typedef struct Point
{
    uint x;
    uint y;
    uint wait_points;
    uint visits;
} Point;

/* abstract class for a point
 * to get a new car, use u_new_car */
typedef struct Car
{
    Point position;
    Point *goals;
    ushort goal_index;
    double speed;
    double desired_speed;
    double reaction_time;

} Car;

/* compute the distance betweeen two points
 * more expensive than u_distance_sqr */
double u_distance(Point, Point);

/* compute the distance squared between two points
 * less expensive than u_distance */
double u_distance_sqr(Point, Point);

/* generate a new point with default values set */
Point u_new_point(uint x, uint y);
/* generate a new car with default values set */
Car u_new_car(Point start, Point *goals);

/* helper function for printing a point */
void u_print_point(Point);
/* helper function for printing a car */
void u_print_car(Car);

void file_reader(char *file_name);
