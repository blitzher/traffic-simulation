#include "simulation.h"
#define MAX_VEHICLES 1000

/* internal helper function for sim */
utiny_i need_more_cars();

/* internal helper function for sim */
void move_car_toward_goal(Car c);

/* internal helper function for sim */
utiny_i check_goal(Car c);

void s_run_simulation(Config config)
{
    int time;
    int i;
    Point *start;
    Point *goals;
    Car all_vehicles[MAX_VEHICLES];
    printf("running simulation...\n");

    u_print_configs(config);

    /* run the simulation  */
    for (time = 0; time < config.sim_duration; time++)
    {
        if (need_more_cars())
        {
            /* TODO: Make dynmaic route system */
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

        for (i = 0; i < MAX_VEHICLES; i++)
        {
            move_car_toward_goal(all_vehicles[i]);
            /* TODO: Check for collision */

            if (u_distance_sqr(*all_vehicles[i].position, all_vehicles[i].goals[all_vehicles[i].goal_index]) < 2)
            {
                all_vehicles[i].goals[all_vehicles[i].goal_index].visits++;

                if (all_vehicles[i].goals[all_vehicles[i].goal_index] == goal_point)
                {
                    all_vehicles[i].init = 0;
                }
                else
                {
                    all_vehicles[i].goal_index++;
                }
            }
        }
    }
}

/* internal helper function for sim */
utiny_i need_more_cars()
{
    return 1;
}

/* internal helper function for sim */
void move_car_toward_goal(Car c)
{
    return;
}
