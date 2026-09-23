/*
** EPITECH PROJECT, 2021
** handle_matrix.c
** File description:
** fill and multiply matrix
*/

#include "includes/my.h"

void mult_matrix(double *mat, double *reloaded)
{
    int i = 0;
    double tmp[9];

    for (; i < 9; i++)
        tmp[i] = mat[i];

    mat[0] = tmp[0] * reloaded[0] + tmp[1] * reloaded[3] + tmp[2] * reloaded[6];
    mat[1] = tmp[0] * reloaded[1] + tmp[1] * reloaded[4] + tmp[2] * reloaded[7];
    mat[2] = tmp[0] * reloaded[2] + tmp[1] * reloaded[5] + tmp[2] * reloaded[8];
    mat[3] = tmp[3] * reloaded[0] + tmp[4] * reloaded[3] + tmp[5] * reloaded[6];
    mat[4] = tmp[3] * reloaded[1] + tmp[4] * reloaded[4] + tmp[5] * reloaded[7];
    mat[5] = tmp[3] * reloaded[2] + tmp[4] * reloaded[5] + tmp[5] * reloaded[8];
    mat[6] = tmp[6] * reloaded[0] + tmp[7] * reloaded[3] + tmp[8] * reloaded[6];
    mat[7] = tmp[6] * reloaded[1] + tmp[7] * reloaded[4] + tmp[8] * reloaded[7];
    mat[8] = tmp[6] * reloaded[2] + tmp[7] * reloaded[5] + tmp[8] * reloaded[8];
}

void fill_rot_matrix(double *matrix, double nb)
{
    double cos_nb = cos(nb);
    double sin_nb = sin(nb);

    matrix[0] = cos_nb;
    matrix[1] = -sin_nb;
    matrix[2] = 0;
    matrix[3] = sin_nb;
    matrix[4] = cos_nb;
    matrix[5] = 0;
    matrix[6] = 0;
    matrix[7] = 0;
    matrix[8] = 1;
}

void fill_ref_matrix(double *matrix, double nb)
{
    double cos_nb = cos(2 * nb);
    double sin_nb = sin(2 * nb);

    matrix[0] = cos_nb;
    matrix[1] = sin_nb;
    matrix[2] = 0;
    matrix[3] = sin_nb;
    matrix[4] = -cos_nb;
    matrix[5] = 0;
    matrix[6] = 0;
    matrix[7] = 0;
    matrix[8] = 1;
}
