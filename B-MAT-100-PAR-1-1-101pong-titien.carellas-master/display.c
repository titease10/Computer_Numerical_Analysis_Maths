/*
** EPITECH PROJECT, 2021
** display.c
** File description:
** display
*/

#include <stdio.h>
#include "includes/struct.h"
#include "includes/my.h"

void display_velocity(vector_t vel)
{
    printf("The velocity vector of the ball is:\n");
    printf("(%.2f, %.2f, %.2f)\n", vel.x, vel.y, vel.z);
}

void display_coordinates(vector_t coor, int n)
{
    printf("At time t + %i, ball coordinates will be:\n", n);
    printf("(%.2f, %.2f, %.2f)\n", coor.x, coor.y, coor.z);
}

void display_angle(float angle)
{
    printf("The incidence angle is:\n");
    printf("%.2f degrees\n", angle);
}
