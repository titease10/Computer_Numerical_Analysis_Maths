/*
** EPITECH PROJECT, 2021
** my.h
** File description:
** header file
*/

#ifndef MY_H_
#define MY_H_

#include "struct.h"

vector_t calc_velocity(vector_t vn, vector_t v0);
vector_t calc_coordinates(vector_t velocity, vector_t vn, int n);
float calc_angle(vector_t vec);
void display_velocity(vector_t vel);
void display_coordinates(vector_t coor, int n);
void display_angle(float angle);
float norm_vec(vector_t v1);
int verif_touch(vector_t v2, vector_t vel);
int verif_arg(int argc, char **argv);

#endif
