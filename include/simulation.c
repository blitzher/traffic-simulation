#include "simulation.h"
#include "string.h"
#include "colours.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_VEHICLES 1000

#define COL_DET 8
#define CAR_DIST_SQR 18 /* required free space between vehicles */

/* internal helper function for sim */
utiny_i on_last_goal(Car *c);
utiny_i need_more_cars();
void calculate_car_position(uint index, Car *cars, Vector *);
utiny_i is_valid_position(uint index, Vector *pos, Car *all_cars);
utiny_i check_goal(Car c);
uint count_cars(Car *cars);
void change_lights(uint);

void s_run_simulation(Config config)
{
    uint time, i;
    uint max_conc_cars = 0;
    uint total_vehicle_age = 0;
    Route goals;

    Car *current_car;
    Point *current_goal;
    Vector *upcoming_positions = (Vector *)malloc(sizeof(Vector) * MAX_VEHICLES);

    char line[80];
    FILE *fp = fopen(".visuals", "w");   

    uint cars_spawned = 0;
    Car *all_vehicles = (Car *)malloc(sizeof(Car) * MAX_VEHICLES);

    if (DEBUG)
    {
        u_print_configs(config);
    }
    c_printf("\nrunning simulation...\n\n", YEL);

    /* make into function for refinement? */
    /* run the simulation  */
    for (time = 0; time < config.sim_duration; time++)
    {

        /* update the traffic lights, based on the current time */
        change_lights(time);

        sprintf(line, "%u %u %u %u ", 
                            r_all_points[3]->light,
                            r_all_points[8]->light,
                            r_all_points[4]->light,
                            r_all_points[7]->light );
        fputs(line, fp);


        max_conc_cars = count_cars(all_vehicles) > max_conc_cars ? count_cars(all_vehicles) : max_conc_cars;

        if (need_more_cars(cars_spawned, config.car_total_amount,
                           time, config.sim_duration))
        {
            goals = r_random_route();

            for (i = 0; i < MAX_VEHICLES; i++)
            {
                if (all_vehicles[i].init != 1)
                {
                    all_vehicles[i] = u_new_car(goals);
                    cars_spawned++;
                    break;
                }
            }
        }

        /* For every car in the simulation, find out
         * where it should go */
        for (i = 0; i < MAX_VEHICLES; i++)
        {
            /* if car is dead, go to next car */
            if (all_vehicles[i].init != 1)
            {
                continue;
            }

            current_car = &all_vehicles[i];
            current_goal = current_car->route.points[current_car->goal_index];

            /* write down the current car into file */
            sprintf(line, "%.0f %.0f ", current_car->position.x, current_car->position.y);
            fputs(line, fp);

            /* check for goal */
            if (u_distance(current_car->position, v_from_point(*current_goal)) <= u_configs.point_radius)
            {
                /* if it's the last goal */
                if (on_last_goal(current_car))
                {
                    /* car go die and gets replaced. */
                    current_car->init = 0;
                    total_vehicle_age += current_car->age;
                    current_goal->visits++;
                }
                else if (current_goal->light == green)
                {
                    /* otherwise, set next goal to current goal */
                    current_car->goal_index++;
                    current_goal->visits++;
                }
            }

            calculate_car_position(i, all_vehicles, &upcoming_positions[i]);
            current_car->age++;

            /* if car is adequately close to its current goal */
            /* TODO: handle concurrect collisions cleanly */
        }

        /* Move every car according to its newfound position */
        for (i = 0; i < MAX_VEHICLES; i++)
        {
            if (all_vehicles[i].init != 1)
            {
                continue;
            }

            current_car = &all_vehicles[i];
            current_goal = current_car->route.points[current_car->goal_index];

            current_car->position = upcoming_positions[i];
        }
        sprintf(line, "\n");
        fputs(line, fp);
    }

    u_configs.o_conc_cars = max_conc_cars;
    u_configs.o_total_vehicle_age = total_vehicle_age;

    if (DEBUG)
    {
        printf("max conc cars: %d\n", max_conc_cars);
        printf("cars at end of sim: %d\n", count_cars(all_vehicles));
    }

    /* frees allocated memory. */
    free(all_vehicles);
    free(upcoming_positions);
    fclose(fp);
}

/* figure out if a cars current goal 
 * is the last in its route */
utiny_i on_last_goal(Car *c)
{
    utiny_i i;
    utiny_i last_goal_index = 5;

    for (i = 0; i < MAX_ROUTE_LEN; i++)
    {
        if (c->route.points[i]->init == 1)
        {
            last_goal_index = i;
        }
    }
    return c->goal_index == last_goal_index;
}

/* internal helper function for sim */
utiny_i need_more_cars(uint curr_veh, uint total_veh,
                       uint curr_time, uint total_time)
{
    float time_per_car = (float)total_time / (float)total_veh;
    float veh_time = (float)curr_veh * time_per_car;

    return curr_time > veh_time;
}

/* internal helper function for sim */
void calculate_car_position(uint index, Car *all_cars, Vector *output)
{
    int i;
    Car *car = &all_cars[index];
    Point *current_goal = car->route.points[car->goal_index];

    /* Creates vector values from car position to goal */
    double dx = current_goal->x - car->position.x;
    double dy = current_goal->y - car->position.y;

    Vector direction = v_new_vector(dx, dy);
    Vector normalized = v_normalize(direction);

    Vector car_delta_position;
    Vector next_position;
    Vector goal_position = v_new_vector(current_goal->x, current_goal->y);

    /* printf("------------\n");
    u_print_car(*car); */
    for (i = 1; i <= COL_DET; i++)
    {
        car_delta_position = v_scale(normalized, (float)car->speed * (i) / COL_DET);
        next_position = v_add(car->position, car_delta_position);

        if (!is_valid_position(index, &next_position, all_cars))
        {
            i--;
            break;
        }

        if (u_distance(next_position, goal_position) <= u_configs.point_radius) {
            break;
        }
    }

    if (i == 0)
    {
        current_goal->wait_points++;
        *output = car->position;
    }
    else
    {
        *output = next_position;
    }
}

utiny_i is_valid_position(uint index, Vector *pos, Car *all_cars)
{
    Car *car = &all_cars[index];
    Point *current_goal = car->route.points[car->goal_index];
    double dist_to_goal;
    int i;

    /* if light is red, and sufficiently close, stop */
    if (car->goal_index == 1)
    {
        dist_to_goal = u_distance(*pos, v_from_point(*current_goal));

        if (current_goal->light == red && dist_to_goal <= u_configs.point_radius)
        {
            return 0;
        }
    }

    /* Check all_vehicles current position for collision and
     * compare to current output vector. */

    for (i = 0; i < MAX_VEHICLES; i++)
    {
        if (all_cars[i].init != 1 || index == i)
        {
            continue;
        }

        /* here we explicitly use distance squared for performance reasons */

        /* if (car->route.points[3]->init && u_distance_sqr(*pos, all_cars[i].position) < CAR_DIST_SQR * 1.5) {
            return 0;
        } */

        if (u_distance_sqr(*pos, all_cars[i].position) < CAR_DIST_SQR)
        {
            return 0;
        }
    }
    return 1;
}

/* Counts and returns amount of alive cars. */
uint count_cars(Car *cars)
{
    uint i, j = 0;
    for (i = 0; i < MAX_VEHICLES; i++)
    {
        if (cars[i].init != 1)
        {
            j++;
        }
    }
    return MAX_VEHICLES - j;
}

void change_lights(uint time)
{
    static uint yellow = 3;
    uint light_period = (u_configs.traffic_light_green + u_configs.traffic_light_red) + (2 * yellow);
    uint point_in_period = time % light_period;

    /* light #3 and #8 */
    if (point_in_period < u_configs.traffic_light_green)
    {
        r_all_points[3]->light = 1;
        r_all_points[8]->light = 1;
        r_all_points[4]->light = 0;
        r_all_points[7]->light = 0;
    }
    else if ( point_in_period > u_configs.traffic_light_green + yellow && 
              point_in_period < light_period - yellow)
    {
        r_all_points[3]->light = 0;
        r_all_points[8]->light = 0;
        r_all_points[4]->light = 1;
        r_all_points[7]->light = 1;
    }
    else {
        r_all_points[3]->light = 0;
        r_all_points[8]->light = 0;
        r_all_points[4]->light = 0;
        r_all_points[7]->light = 0;
    }
}
