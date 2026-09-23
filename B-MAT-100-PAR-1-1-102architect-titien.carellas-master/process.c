/*
** EPITECH PROJECT, 2021
** process.c
** File description:
** process the function
*/

#include "includes/my.h"

void do_translation(int pos, char **av, double *matrix, double *res)
{
    double x = atof(av[pos + 1]);
    double y = atof(av[pos + 2]);

    matrix[2] += x;
    matrix[5] += y;
    res[0] += x;
    res[1] += y;
    printf("Translation along vector (%.0f, %.0f)\n", x, y);
}

void do_scaling(int pos, char **av, double *matrix, double *res)
{
    double x = atof(av[pos + 1]);
    double y = atof(av[pos + 2]);

    for (int i = 0; i < 6; i++) {
        matrix[i] *= ((i <= 2) ? x : y);
        if (matrix[i] == 0)
            matrix[i] = 0;
    }
    res[0] *= x;
    res[1] *= y;
    printf("Scaling by factors %.0f and %.0f\n", x, y);
}

void do_rotation(int pos, char **av, double  *matrix, double *res)
{
    double nb = atof(av[pos + 1]);
    double reloaded[9];
    double temp_zero = res[0];
    double temp_one = res[1];

    nb = (nb * M_PI) / 180;
    fill_rot_matrix(&reloaded[0], nb);
    mult_matrix(&matrix[0], &reloaded[0]);
    res[0] = temp_zero * reloaded[0] + temp_one * reloaded[1];
    res[1] = temp_zero * reloaded[3] + temp_one * reloaded[4];
    printf("Rotation by a %s degree angle\n", av[pos + 1]);
}

void do_reflection(int pos, char**av, double *matrix, double *res)
{
    double nb = atof(av[pos + 1]);
    double reloaded[9];
    double temp_zero = res[0];
    double temp_one = res[1];

    nb = (nb * M_PI) / 180;
    fill_ref_matrix(&reloaded[0], nb);
    mult_matrix(&matrix[0], &reloaded[0]);
    res[0] = temp_zero * reloaded[0] + temp_one * reloaded[1];
    res[1] = temp_zero * reloaded[3] + temp_one * reloaded[4];
    printf("Reflection over an axis with an inclination angle");
    printf(" of %s degrees\n", av[pos + 1]);
}
