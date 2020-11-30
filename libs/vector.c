#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "colours.h"

double v_check_if_parallel(Vector vec_a, Vector vec_b)
{
    return (v_crossproduct(vec_a, vec_b) == 0);
}

double v_crossproduct(Vector vec_a, Vector vec_b)
{
    if ((vec_a.x == 0 && vec_a.y == 0) || (vec_b.x == 0 && vec_b.y == 0))
    {
        c_printf("Warning: ", MAG);
        printf("you are trying to calculate the crossproduct with a 0 vector!\n");
    }

    return vec_a.x * vec_b.y - vec_a.y * vec_b.x;
}
