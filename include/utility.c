#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "utility.h"
#include "routes.h"
#include "colours.h"

#define MAX_LINE_LENGTH 80

void sanitise_config(Config);

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

Point *u_new_point(utiny_i x, utiny_i y)
{
    Point *p = (Point *)malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    p->wait_points = 0;
    p->visits = 0;

    /* has been properly initialised */
    p->init = 1;
    return p;
}

Car u_new_car(Route route)
{
    Car c;

    c.position = v_from_point(*route.points[0]);
    c.route = route;
    c.route.points[0]->visits++;
    c.goal_index = 1;
    c.age = 0;
    /* load relevant information from config struct */
    c.speed = u_configs.car_initial_speed;
    /* has been properly initialised */
    c.init = 1;
    return c;
}

/* print helper functions */

/* TODO: print as a coordinate in north/south/east/west space instead */
void u_print_point(Point *p)
{
    printf("< x: %d, y: %d\n", p->x, p->y);
    printf("  wait_points: %d, visits: %d >\n", p->wait_points, p->visits);
}

void u_print_car(Car c)
{
    printf("Position:\n");
    u_print_vector(&c.position);
    printf("Current goal index: %d\n", c.goal_index);
    printf("Current goal:\n");
    u_print_point(c.route.points[c.goal_index]);
}

void u_print_route(Route route)
{
    printf("%s\n", route.name);
}

void u_print_configs(Config con)
{
    printf("Configurations:\n");
    printf("car-initial-speed: %f\n", con.car_initial_speed);
    printf("point-radius: %f\n", con.point_radius);
    printf("traffic-light-green: %d\n", con.traffic_light_green);
    printf("traffic-light-red: %d\n", con.traffic_light_red);
    printf("sim-duration: %d\n", con.sim_duration);
    printf("amount-of-cars-simulated: %u\n", con.car_total_amount);
    printf("chance-of-traffic-from-north: %u\n", con.traffic_from_north);
    printf("chance-of-traffic-from-south: %u\n", con.traffic_from_south);
    printf("chance-of-traffic-from-east: %3u\n", con.traffic_from_east);
    printf("chance-of-traffic-from-west: %3u\n", con.traffic_from_west);
}
void u_print_vector(Vector *vec)
{
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
            if (strcmp(name, "car-initial-speed") == 0)
            {
                out->car_initial_speed = atof(value_string);
            }
            else if (strcmp(name, "car-total-amount") == 0)
            {
                out->car_total_amount = atoi(value_string);
            }
            else if (strcmp(name, "point-radius") == 0)
            {
                out->point_radius = atof(value_string);
                /* also store the squared radius, for improved
                 * collision detection efficiency */
                out->point_radius_sqr = pow(atof(value_string), 2);
            }
            else if (strcmp(name, "traffic-light-green") == 0)
            {
                out->traffic_light_green = atoi(value_string);
            }
            else if (strcmp(name, "traffic-light-red") == 0)
            {
                out->traffic_light_red = atoi(value_string);
            }
            else if (strcmp(name, "sim-duration") == 0)
            {
                out->sim_duration = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-traffic-from-south") == 0)
            {
                out->traffic_from_south = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-south-to-north") == 0)
            {
                out->south_to_north = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-south-to-east") == 0)
            {
                out->south_to_east = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-south-to-west") == 0)
            {
                out->south_to_west = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-traffic-from-north") == 0)
            {
                out->traffic_from_north = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-north-to-south") == 0)
            {
                out->north_to_south = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-traffic-from-east") == 0)
            {
                out->traffic_from_east = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-east-to-south") == 0)
            {
                out->east_to_south = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-east-to-north") == 0)
            {
                out->east_to_north = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-east-to-west") == 0)
            {
                out->east_to_west = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-traffic-from-west") == 0)
            {
                out->traffic_from_west = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-west-to-south") == 0)
            {
                out->west_to_south = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-west-to-east") == 0)
            {
                out->west_to_east = atoi(value_string);
            }
            else if (strcmp(name, "chance-of-west-to-north") == 0)
            {
                out->west_to_north = atoi(value_string);
            }
            else
            {
                if (DEBUG)
                {
                    printf("unaccounted config: %s\n", name);
                }
            }
        }
    }

    fclose(fp);

    /* after loading config into struct,
     * validate that config data is valid */
    sanitise_config(*out);

    return 1;
}

int u_compile_output(char *output_file, char *config_name)
{
    unsigned int total_visit = 0, total_wait_points = 0;
    uint i;
    FILE *fp;
    Point *point;
    char line[160];

    fp = fopen(output_file, "w");
    sprintf(line, "config name: %s\n", config_name);
    fputs(line, fp);

    sprintf(line, "\npositions of points:\n\t    0 1\n\n\t2   3 4   5\n\t6   7 8   9\n\n\t   10 11\n\n");
    fputs(line, fp);

    /* iterate over all points */
    for (i = 0; i < TOTAL_POINTS; i++)
    {
        point = r_point_by_index(i);
        sprintf(line, "point:%2d <x:%3d, y:%3d - visits:%5d, iterations waited:%5d>\n",
                i, point->x, point->y, point->visits, point->wait_points);
        total_visit += point->visits;
        total_wait_points += point->wait_points;
        fputs(line, fp);
    }
    sprintf(line, "\n# Total amount of vehicles being simulated\n\tAmount of vehicles:%6d\n", u_configs.car_total_amount);
    fputs(line, fp);
    sprintf(line, "\n# Total amounts of points reached by vehicles\n\tSum of visits:%6u\n", total_visit);
    fputs(line, fp);
    sprintf(line, "\n# Total seconds cars were standing still\n\tTotal wait points:%7u\n\tAverage pr second:%7.2f\n\tAverage pr vehicle:%7.2f\n",
            total_wait_points,
            (float)total_wait_points / (float)u_configs.sim_duration,
            (float)total_wait_points / (float)u_configs.car_total_amount);
    fputs(line, fp);
    sprintf(line, "\n# Most vehicles alive at same time\n\tMax concurrent vehicles:%6u\n", u_configs.o_conc_cars);
    fputs(line, fp);
    sprintf(line, "\n# Average iterations of vehicle to complete its route\n\tAverage iterations for completion:%7.2f iterations\n",
            (float)u_configs.o_total_vehicle_age / (float)u_configs.car_total_amount);
    fputs(line, fp);
    fclose(fp);
    return 1;
}

void sanitise_config(Config config)
{
    int sum, throw_flag = 0;
    /* can only summon 1 car per frame */
    if (config.sim_duration < config.car_total_amount)
    {
        warn("( ) too many cars for simulation duration!\n");
    }

    /* check that origin percentages add up to 100 */
    sum = config.traffic_from_north +
          config.traffic_from_south +
          config.traffic_from_west +
          config.traffic_from_east;

    if (sum != 100)
    {
        warn("(*) traffic from different directions do not add up to 100%%!\n");
        throw_flag = 1;
    }

    /* north can only go south, so should always be 100% */
    if (config.north_to_south != 100)
    {
        warn("(*) traffic from north to south is not 100!\n");
        throw_flag = 1;
    }

    /* all traffic from south should add up to 100% */
    sum = config.south_to_east +
          config.south_to_north +
          config.south_to_west;

    if (sum != 100 && config.traffic_from_south > 0)
    {
        warn("(*) traffic from south does not add up to 100%%!\n");
        throw_flag = 1;
    }

    /* all traffic from east should add up to 100% */
    sum = config.east_to_north +
          config.east_to_south +
          config.east_to_west;

    if (sum != 100 && config.traffic_from_east > 0)
    {
        warn("(*) traffic from east does not add up to 100%%!\n");
        throw_flag = 1;
    }

    /* all traffic from west should add up to 100% */
    sum = config.west_to_east +
          config.west_to_north +
          config.west_to_south;

    if (sum != 100 && config.traffic_from_west > 0)
    {
        warn("(*) traffic from west does not add up to 100%%!\n");
        throw_flag = 1;
    }

    if (throw_flag)
    {
        error("    one or more critical warnings are unsolved!\n");
    }
}
