/*
** EPITECH PROJECT, 2021
** creat_vector.c
** File description:
** creat_vector
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "includes/struct.h"

vector_t creat_vector(char *x, char *y, char *z)
{
    vector_t res;

    res.x = atof(x);
    res.y = atof(y);
    res.z = atof(z);
    return (res);
}
