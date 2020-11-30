#pragma once

/* Struct of a vector consisting of an x and y coordinate,
 as well as the length of the vector */
typedef struct Vector
{
    int x;
    int y;
    double length;
} Vector;


/* generate a new vector from two coordinates */
Vector v_new_vector(int x, int y);

/* compute the dot product between two vectors  */
double v_dotp(Vector vec_a, Vector vec_b);

/* calculate the crossproduct of 2 vectors */
double v_crossproduct(Vector vec_a, Vector vec_b);

/* compute the angle between two vectors */
double v_angle_between(Vector vec_a, Vector vec_b);

/* check if 2 vectors are paralel by checking if 
 * the crossproduct is either 0 or something else */
double v_check_if_parallel(Vector vec_a, Vector vec_b);
