#include "vector.h"

#include <stdio.h>
#include <math.h>
#include "colours.h"
#include "utility.h"

Vector v_new_vector(double x, double y) {
    Vector out;
    out.x = x;
    out.y = y;

    return out;
}

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

double v_magnitude(Vector vec_a)
{
    return sqrt((pow(vec_a.x, 2) + pow(vec_a.y, 2)));
}

Vector v_normalize(Vector vec_a)
{
    double vec_len = v_magnitude(vec_a);

    return v_scale(vec_a, 1 / vec_len);
}

Vector v_add(Vector vec_a, Vector vec_b)
{

    return v_new_vector(vec_a.x + vec_b.x,
                        vec_a.y + vec_b.y);
}

Vector v_scale(Vector vec_a, double scalar)
{

    return v_new_vector(vec_a.x * scalar,
                        vec_a.y * scalar);
}

Vector v_from_point(Point p)
{

    return v_new_vector(p.x, p.y);
}
