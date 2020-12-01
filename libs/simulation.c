#include "simulation.h"
#define MAX_VEHICLES 1000

/* internal helper function for sim */
utiny_i need_more_cars();
utiny_i on_last_goal(Car *c);
void move_car_toward_goal(Car *c);
utiny_i check_goal(Car c);
uint count_cars(Car *cars);

void s_run_simulation(Config config)
{
    int time;
    int i, j;
    Point *start;
    Point *goals;

    Car *current_car;
    Point *current_goal;

    Car *all_vehicles = (Car *)malloc(sizeof(Car) * MAX_VEHICLES);

    u_print_configs(config);
    printf("\nrunning simulation...\n");

    /* run the simulation  */
    for (time = 0; time < config.sim_duration; time++)
    {
        /* if (DEBUG) { printf("time = %d\n", time); } */

        if (need_more_cars())
        {
            /* TODO: Make dynamic route system */
            goals = r_north_bound_routes[2];
            start = &goals[0];

            for (i = 0; i < MAX_VEHICLES; i++)
            {
                if (all_vehicles[i].init == 0)
                {
                    all_vehicles[i] = u_new_car(start, goals);
                    break;
                }
            }
        }
        /* 
        if (DEBUG) {printf("%u cars in sim...\n", count_cars(all_vehicles));} */

        for (i = 0; i < MAX_VEHICLES; i++)
        {
            /* if car is dead, go to next car */
            if (all_vehicles[i].init != 1)
            {
                /* Doesn't serve purpose but good practice wpgg*/
                for (j = i; j < MAX_VEHICLES; j++)
                {
                    if (all_vehicles[j].init == 1)
                    {
                        break;
                    }
                }
                i = j;
                continue;
            }

            current_car = &all_vehicles[i];
            current_goal = &current_car->goals[current_car->goal_index];

            move_car_toward_goal(&all_vehicles[i]);
            /* TODO: Check for collision */

            /* Checking speed under 1, standstill occurs and increment wait_points. */
            if (current_car->speed < 1)
            {
                current_goal->wait_points++;
            }

            /* if car is adequately close to its current goal */
            if (u_distance_sqr(*current_car->position, v_from_point(*current_goal)) < 2)
            {
                current_goal->visits++;

                /* if it's the last goal */
                if (on_last_goal(current_car))
                {
                    /* yeet */
                    all_vehicles[i].init = 0;
                }
                else
                {
                    /* otherwise, set next goal to current goal */
                    all_vehicles[i].goal_index++;
                }
            }
        }
    }
    /* fly free my little memory, flyyyyyy */
    free(all_vehicles);
}

/* figure out if a cars current goal 
 * is the last in its route */
utiny_i on_last_goal(Car *c)
{
    utiny_i i;
    utiny_i last_goal_index;

    for (i = 0; i < MAX_ROUTE_LEN; i++)
    {
        if (c->goals[i].init == 1)
        {
            last_goal_index = i;
        }
    }
    return c->goal_index == last_goal_index;
}

/* internal helper function for sim */
/* TODO: implement */
utiny_i need_more_cars()
{
    return 1;
}

/* internal helper function for sim */
void move_car_toward_goal(Car *car)
{
    Point *current_goal = &car->goals[car->goal_index];

    double dx = current_goal->x - car->position->x;
    double dy = current_goal->y - car->position->y;

    Vector direction = v_new_vector(dx, dy);
    Vector normalized = v_normalize(direction);

    /* new car position found */
    Vector car_new_position = v_scale(normalized, car->speed);

    /* assign new position to car */
    Vector new_position = v_add(*car->position, car_new_position);
    car->position = &new_position;
}

uint count_cars(Car *cars)
{
    uint i;
    for (i = 0; i < MAX_VEHICLES; i++)
    {
        if (cars[i].init != 1)
        {
            break;
        }
    }
    return i;
}
