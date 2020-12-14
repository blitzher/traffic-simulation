#include "vector.h"

#include <stdio.h>
#include <math.h>
#include "colours.h"
#include "utility.h"

Vector v_new_vector(double x, double y)
{
    Vector out;
    out.x = x;
    out.y = y;

    return out;
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
