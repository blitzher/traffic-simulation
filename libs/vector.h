#pragma once

/* Struct of a vector consisting of an x and y coordinate,
 as well as the length of the vector */
typedef struct Vector
{
    int x;
    int y;
    double length;
} Vector;

/* Function to calculate the crossproduct of 2 vectors */
double v_crossproduct(Vector vec_a, Vector vec_b);
/* Function to check if 2 vectors are paralel by checking if 
the crossproduct is either 0 or something else */
double v_check_if_parallel(Vector vec_a, Vector vec_b);
