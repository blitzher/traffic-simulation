#include "simulation.h"
#include "string.h"
#define MAX_VEHICLES 1000

/* internal helper function for sim */
utiny_i need_more_cars();
utiny_i on_last_goal(Car *c);
void move_car_toward_goal(Car *c, Vector*);
utiny_i check_goal(Car c);
uint count_cars(Car *cars);

void s_run_simulation(Config config)
{
    int time;
    int i;
    Route goals;

    Car *current_car;
    Point *current_goal;
    Vector *upcoming_positions = (Vector *)malloc(sizeof(Vector)*MAX_VEHICLES);

    uint cars_spawned = 0;
    Car *all_vehicles = (Car *)malloc(sizeof(Car) * MAX_VEHICLES);

    u_print_configs(config);
    printf("\nrunning simulation...\n\n");

    /* make into function for refinement? */
    /* run the simulation  */
    for (time = 0; time < config.sim_duration; time++)
    {
        if(DEBUG) { printf("time: %d\n", time);}
        if (time % 100 == 0)
        {
        }
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



        /* For every car in the simulation, check goals and if its final goal. */
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
            move_car_toward_goal(current_car, &upcoming_positions[i]);

            /* Checking speed under 1, standstill occurs and increment wait_points. */
            if (current_car->speed < 1)
            {
                current_goal->wait_points++;
            }

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

            if (u_distance_sqr(current_car->position, v_from_point(*current_goal)) < 12)
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
    if (total_veh > curr_time)
    {
        return 1;
    }
    return 0;
    /* float time_per_car = (float)total_time / (float)total_veh;
    float veh_time = (float)curr_veh * time_per_car;

    return curr_time > veh_time; */
}

/* internal helper function for sim */
void move_car_toward_goal(Car *car, Vector* output)
{
    Point *current_goal = car->route.points[car->goal_index];

    double dx = current_goal->x - car->position.x;
    double dy = current_goal->y - car->position.y;

    Vector direction = v_new_vector(dx, dy);
    Vector normalized = v_normalize(direction);

    /* new car position found */
    Vector car_new_position = v_scale(normalized, car->speed);

    /* assign new position to car */
    Vector new_position = v_add(car->position, car_new_position);
    *output = new_position;
}

/* Counts and returns amount of alive cars. */
uint count_cars(Car *cars)
{
    uint i, j;
    for (i = 0; i < MAX_VEHICLES; i++)
    {
        if (cars[i].init != 1)
        {
            j++;
        }
    }
    return MAX_VEHICLES - j;
}
