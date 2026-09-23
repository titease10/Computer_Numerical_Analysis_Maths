/*
** EPITECH PROJECT, 2021
** struct.h
** File description:
** struct
*/

#ifndef STRUCT_H_
#define STRUCT_H_
#include <stdbool.h>

typedef struct vector_s {
    float x;
    float y;
    float z;
} vector_t;

vector_t creat_vector(char *x, char *y, char *z);
float norm_vec(vector_t v1);

#endif
