#pragma once

#include <stdio.h>
#include <math.h>

/* Struct of a vector consisting of an x and y coordinate,
 as well as the length of the vector */
typedef struct Vector
{
    double x;
    double y;
    double length;
} Vector;

/* generate a new vector from two coordinates */
Vector v_new_vector(double x, double y);

/* compute the dot product between two vectors  */
double v_dotp(Vector vec_a, Vector vec_b);

/* calculate the crossproduct of 2 vectors */
double v_crossproduct(Vector vec_a, Vector vec_b);

/* compute the angle between two vectors */
double v_angle_between(Vector vec_a, Vector vec_b);

/* check if 2 vectors are paralel by checking if 
 * the crossproduct is either 0 or something else */
double v_check_if_parallel(Vector vec_a, Vector vec_b);
/* Calculate the length of a vector */
double v_magnitude(Vector);

/* return a vector of same direction, but with length 1 */
Vector v_normalize(Vector);

/* adds two vectors, and return their sum */
Vector v_add(Vector, Vector);

/* scale a vector by a number, and return the resulting vector */
Vector v_scale(Vector, double);

#include "utility.h"
/* return a vector from a point */
Vector v_from_point(Point);