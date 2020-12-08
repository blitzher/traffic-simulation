#include "simulation.h"
#include "string.h"
#define MAX_VEHICLES 1000

/* internal helper function for sim */
utiny_i need_more_cars();
utiny_i on_last_goal(Car *c);
void move_car_toward_goal(uint index, Car *cars, Vector *);
utiny_i check_goal(Car c);
uint count_cars(Car *cars);
void change_lights(uint);

void s_run_simulation(Config config)
{
    uint time, i;
    uint max_conc_cars = 0;
    Route goals;

    Car *current_car;
    Point *current_goal;
    Vector *upcoming_positions = (Vector *)malloc(sizeof(Vector) * MAX_VEHICLES);

    uint cars_spawned = 0;
    Car *all_vehicles = (Car *)malloc(sizeof(Car) * MAX_VEHICLES);

    u_print_configs(config);
    printf("\nrunning simulation...\n\n");

    /* make into function for refinement? */
    /* run the simulation  */
    for (time = 0; time < config.sim_duration; time++)
    {

        /* update the traffic lights, based on the current time */
        change_lights(time);

        max_conc_cars = count_cars(all_vehicles) > max_conc_cars ? count_cars(all_vehicles) : max_conc_cars;

        if (need_more_cars(cars_spawned, config.car_total_amount,
                           time, config.sim_duration))
        {
            /* TODO: Make dynamic route system */
            goals = r_random_route();

            for (i = 0; i < MAX_VEHICLES; i++)
            {
                if (all_vehicles[i].init == 0)
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

            /* TODO: handle concurrect collisions cleanly */
            move_car_toward_goal(i, all_vehicles, &upcoming_positions[i]);

            /* if car is adequately close to its current goal */
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

            if (u_distance_sqr(current_car->position, v_from_point(*current_goal)) < 16)
            {
                current_goal->visits++;

                /* if it's the last goal */
                if (on_last_goal(current_car))
                {
                    /* car go die and gets replaced. */
                    current_car->init = 0;
                }
                else
                {
                    /* otherwise, set next goal to current goal */
                    current_car->goal_index++;
                }
            }
        }
    }

    if (DEBUG)
    {
        printf("max conc cars: %d\n", max_conc_cars);
        printf("cars at end of sim: %d\n", count_cars(all_vehicles));
    }

    /* frees allocated memory. */
    free(all_vehicles);
    free(upcoming_positions);
}

/* figure out if a cars current goal 
 * is the last in its route */
utiny_i on_last_goal(Car *c)
{
    utiny_i i;
    utiny_i last_goal_index;

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
void move_car_toward_goal(uint index, Car *all_cars, Vector *output)
{
    uint i;
    double dist_to_goal;
    Car *car = &all_cars[index];
    Point *current_goal = car->route.points[car->goal_index];

    /* Creates vector values from car position to goal */
    double dx = current_goal->x - car->position.x;
    double dy = current_goal->y - car->position.y;

    Vector direction = v_new_vector(dx, dy);
    Vector normalized = v_normalize(direction);

    /* new car position found */
    Vector car_new_position = v_scale(normalized, car->speed);

    /* assign new position to car */
    Vector new_position = v_add(car->position, car_new_position);

    /* check if upcoming traffic light is green */
    if (car->goal_index == 1)
    {
        dist_to_goal = u_distance(car->position, v_from_point(*current_goal));

        /* if light is red, and sufficiently close, stop */

        if (current_goal->light == red && dist_to_goal < 100)
        {
            new_position = car->position;
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

        if (u_distance_sqr(new_position, all_cars[i].position) < u_configs.car_collision_detection_radius)
        {
            new_position = car->position;
            break;
        }
    }

    if (new_position.x == car->position.x && new_position.y == car->position.y)
    {
        current_goal->wait_points++;
    }

    *output = new_position;
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
    uint light_period = u_configs.traffic_light_green + u_configs.traffic_light_red;
    uint point_in_period = time % light_period;

    /* light #3 and #8 */
    if (point_in_period < u_configs.traffic_light_green)
    {
        r_all_points[3]->light = 1;
        r_all_points[8]->light = 1;
        r_all_points[4]->light = 0;
        r_all_points[7]->light = 0;
    }
    else
    {
        r_all_points[3]->light = 0;
        r_all_points[8]->light = 0;
        r_all_points[4]->light = 1;
        r_all_points[7]->light = 1;
    }
}