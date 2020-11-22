#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "utility.h"

#define MAX_LINE_LENGTH 80

Config u_configs;

/* Reads a file and saves it in an array */
int u_load_configs(char *file_name, Config *out)
{
    int i;
    FILE *fp;
    char line[MAX_LINE_LENGTH];

    char value_string[MAX_LINE_LENGTH];
    char name[MAX_LINE_LENGTH];

    int name_end = -1;
    int value_end = -1;

    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", file_name);
        return 0;
    };

    /* read each line of file */
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        /* reset indices to sentinel values */
        name_end = -1;
        value_end = -1;

        /* cut out anything appearing after a '#' */
        for (i = 0; i < MAX_LINE_LENGTH; i++)
        {
            if (line[i] == '#' || line[i] == '\n')
            {
                line[i] = '\0';
            }
        }

        /* find name_end and value_end */
        for (i = 0; i < MAX_LINE_LENGTH && line[i] != '\0'; i++)
        {
            /* look for name_end as long as it is undefined */
            if (name_end == -1 && line[i] == ' ')
            {
                name_end = i;
                continue;
            }
            /* look for value_end, as soon as name_end is defined */
            if (name_end != -1 && value_end == -1 && line[i] == ' ')
            {
                value_end = i;
                break;
            }
        }

        /* if found, export into config struct */
        if (name_end != -1 && value_end != -1)
        {

            strncpy(name, line, name_end);
            name[name_end] = '\0';
            strncpy(value_string, &line[name_end + 1], value_end - name_end - 1);
            value_string[value_end - name_end - 1] = '\0';

            /* implement configurations into output struct */
            if (strcmp(name, "car-acceleration") == 0)
            {
                out->car_acceleration = atof(value_string);
            }
            else if (strcmp(name, "car-initial-speed") == 0)
            {
                out->car_initial_speed = atof(value_string);
            }
            else if (strcmp(name, "car-reaction-time") == 0)
            {
                out->car_reaction_time = atoi(value_string);
            }
            else if (strcmp(name, "point-free-radius") == 0)
            {
                out->point_free_radius = atof(value_string);
            }
            else if (strcmp(name, "weather") == 0)
            {
                out->weather = atoi(value_string);
            }
            else
            {
                printf("unaccounted config: %s\n", name);
            }
        }
    }

    fclose(fp);
    return 1;
}
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

Point u_new_point(utiny_i x, utiny_i y)
{
    Point p;
    p.x = x;
    p.y = y;
    p.wait_points = 0;
    p.visits = 0;
    return p;
}

Car u_new_car(Point *start, Point *goals)
{
    Car c;
    c.position = start;
    c.goals = goals;
    c.goal_index = 0;
    /* load relevant information from config struct */
    c.reaction_time = u_configs.car_reaction_time;
    return c;
}

/* print helper functions */

void u_print_point(Point *p)
{
    printf("< x: %d, y: %d\n", p->x, p->y);
    printf("  wait_points: %d, visits: %d >\n", p->wait_points, p->visits);
}

void u_print_car(Car *c)
{
    printf("Position:\n");
    u_print_point(c->position);
    printf("Current goal:\n");
    u_print_point(&c->goals[c->goal_index]);
}

void u_print_configs(Config *con)
{
    printf("Configurations:\n");
    printf("car-max-acceleration: %f\n", con->car_acceleration);
    printf("car-initial-speed: %f\n", con->car_initial_speed);
    printf("car-reaction-time: %d\n", con->car_reaction_time);
    printf("point-free-radius: %f\n", con->point_free_radius);
    printf("weather: %d", con->weather);
}
