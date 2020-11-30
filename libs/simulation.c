#include "simulation.h"

void s_run_simulation(Config config)
{
    int time;
    Car all_vehicles[1000];
    printf("running simulation...\n");

    u_print_configs(config);


    /* run the simulation  */
    for (time = 0; time < config.sim_duration; time++)
    {
        
    }
}

/* internal helper function for sim */
utiny_i need_more_cars();

/* internal helper function for sim */
void move_car_toward_goal(Car);

/* internal helper function for sim */
utiny_i check_goal(Car);
