/*
** EPITECH PROJECT, 2021
** main.c
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include "includes/my.h"
#include "includes/struct.h"

int main(int argc, char **argv)
{
    vector_t v1;
    vector_t v2;
    vector_t vel;
    vector_t coor;
    float angle = 0;

    if (verif_arg(argc, argv) == 84)
        return (84);
    v1 = creat_vector(argv[1], argv[2], argv[3]);
    v2 = creat_vector(argv[4], argv[5], argv[6]);
    vel = calc_velocity(v2, v1);
    display_velocity(vel);
    coor = calc_coordinates(vel, v2, atoi(argv[7]));
    display_coordinates(coor, atoi(argv[7]));
    if (verif_touch(v2, vel) == 84) {
        printf("The ball won’t reach the paddle.\n");
        return (0);
    }
    angle = calc_angle(vel);
    display_angle(angle);
    return (0);
}
