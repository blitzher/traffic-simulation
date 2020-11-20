#include <stdio.h>
#include <math.h>
#include <string.h>
#include "utility.h"
#include <stdlib.h>
#define MAX_LINE_LENGTH 80

/* Reads a file and saves it in an array */
void file_reader(char *file_name)
{
    FILE *fr;
    int i;
    char arr[MAX_LINE_LENGTH];

    char value_string[MAX_LINE_LENGTH];
    char name[MAX_LINE_LENGTH];
    /* double value; */

    int name_end = -1;
    int value_end = -1;

    fr = fopen(file_name, "r");

    /* read until a newline is found */
    while (fscanf(fr, "%[^\n]", arr) != EOF)
    {
        for (i = 0; i < MAX_LINE_LENGTH; i++)
        {
            /* look for name_end as long as it is undefined */
            if (name_end == -1 && arr[i] == ' ')
            {
                name_end = i;
            }
            /* look for value_end, as soon as name_end is defined */
            if (name_end != -1 && arr[i] == ' ')
            {
                value_end = i;
            }

            /* break after both name and value is found */
            if (name_end != -1 && value_end != -1)
            {
                break;
            }
        }
        strncpy(name, arr, name_end);
        strncpy(value_string, &arr[name_end], value_end - name_end);

        printf("name: %s, value: %s\n", name, value_string);
    }

    fclose(fr);
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
