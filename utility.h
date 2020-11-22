#pragma once

/* define shorthands for
 * unsigned int
 * unsigned short
 * unsigned char, used as tiny int */
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char utiny_i;

/* arbitrary definition of maximum amount of goals */
#define MAX_GOALS 10;

/* abstract struct for configurations
 * to get configurations, use u_load_config
 * 
 * useful for serialization of simulations */
typedef struct Config
{
    double car_acceleration;
    utiny_i car_reaction_time;
    double car_initial_speed;

    double point_free_radius;

    utiny_i weather;

} Config;

/* abstract class for a point
 * to get a new point, use u_new_point */
typedef struct Point
{
    utiny_i x;
    utiny_i y;
    uint wait_points;
    uint visits;
} Point;

/* abstract class for a point
 * to get a new car, use u_new_car */
typedef struct Car
{
    Point *position;
    Point *goals;
    utiny_i goal_index;
    double speed;
    double desired_speed;
    double reaction_time;

} Car;

/* global config variable */
Config u_configs;

/* compute the distance betweeen two points
 * more expensive than u_distance_sqr */
double u_distance(Point, Point);

/* compute the distance squared between two points
 * less expensive than u_distance */
double u_distance_sqr(Point, Point);

/* generate a new config with data loaded from a file
 * and output to output parameter  */
int u_load_configs(char *file_name, Config *out);
/* generate a new point with default values set */
Point u_new_point(utiny_i x, utiny_i y);
/* generate a new car with default values set */
Car u_new_car(Point *start, Point *goals);

/* helper function for printing a point */
void u_print_point(Point *);
/* helper function for printing a car */
void u_print_car(Car *);

/* helper function for printing configs */
void u_print_configs(Config *);
