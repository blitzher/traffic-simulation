#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "utility.h"
#include "routes.h"

#define MAX_LINE_LENGTH 80

Config u_configs;

/* math helper functions */

double u_distance(Vector a, Vector b)
{
    return sqrt(u_distance_sqr(a, b));
}

double u_distance_sqr(Vector a, Vector b)
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

    /* has been properly initialised */
    p.init = 1;
    return p;
}

Car u_new_car(Point *goals)
{
    Car c;
    
    c.position = v_from_point(goals[0]);
    c.goals = goals;
    c.goals[0].visits++;
    c.goal_index = 1;
    /* load relevant information from config struct */
    c.reaction_time = u_configs.car_reaction_time;
    c.speed = 50/3.6;
    /* has been properly initialised */
    c.init = 1;
    return c;
}

/* print helper functions */

void u_print_point(Point *p)
{
    printf("< x: %d, y: %d\n", p->x, p->y);
    printf("  wait_points: %d, visits: %d >\n", p->wait_points, p->visits);
}

void u_print_car(Car c)
{
    printf("Position:\n");
    u_print_vector(&c.position);
    printf("Current goal:\n");
    u_print_point(&c.goals[c.goal_index]);
}

void u_print_route(Point *route)
{
    utiny_i i;

    for (i = 0; i < MAX_ROUTE_LEN && route[i].init == 1; i++)
    {
        u_print_point(&route[i]);
    }
}

void u_print_configs(Config con)
{
    printf("Configurations:\n");
    printf("car-max-acceleration: %f\n", con.car_acceleration);
    printf("car-initial-speed: %f\n", con.car_initial_speed);
    printf("car-reaction-time: %d\n", con.car_reaction_time);
    printf("point-free-radius: %f\n", con.point_free_radius);
    printf("weather: %d\n", con.weather);
    printf("sim-duration: %d\n", con.sim_duration);
}
void u_print_vector(Vector * vec) {
    printf("<x:%.1f, y:%.1f>\n", vec->x, vec->y);
}

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
            else if (strcmp(name, "car-total-amount") == 0)
            {
                out->car_total_amount = atoi(value_string);
            }
            else if (strcmp(name, "point-free-radius") == 0)
            {
                out->point_free_radius = atof(value_string);
            }
            else if (strcmp(name, "weather") == 0)
            {
                out->weather = atoi(value_string);
            }
            else if (strcmp(name, "sim-duration") == 0)
            {
                out->sim_duration = atoi(value_string);
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

int u_compile_output(FILE *output_file)
{
    int i;
    Point *cur_point;
    uint total_wait;

    /* iterate over all points */

    for (i = 0; i < TOTAL_POINTS; i++)
    {
        cur_point = &r_all_points[i];
        total_wait += cur_point->wait_points;
    }
    return 1;
}
void u_print_crossproduct(Vector vec_a, Vector vec_b)
{
    printf("The vectors %s, parallel \n", v_check_if_parallel(vec_a, vec_b) ? "is" : "is not");
}
