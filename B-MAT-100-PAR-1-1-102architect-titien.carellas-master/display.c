/*
** EPITECH PROJECT, 2021
** display_matrix.c
** File description:
** display a matrix
*/

#include "includes/my.h"

void display_result(double nb1, double nb2, double *res)
{
    printf("(%.2f, %.2f) => (%.2f, %.2f)\n", nb1, nb2, res[0], res[1]);
}

void display_matrix(double *matrix)
{
    printf ("%.2f    ", matrix[0]);
    for (int i = 1; i != 8; i++) {
        if ((i + 1) % 3 == 0) {
            printf("%.2f\n", matrix[i]);
            i++;
        }
        printf("%.2f    ", matrix[i]);
    }
    printf("%.2f\n", matrix[8]);
}
