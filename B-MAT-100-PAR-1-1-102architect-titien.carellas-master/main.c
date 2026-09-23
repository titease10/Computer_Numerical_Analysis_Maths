/*
** EPITECH PROJECT, 2021
** main.c
** File description:
** main
*/

#include "includes/my.h"

int main(int ac, char **av)
{
    double matrix[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    double res[2] = {0, 0};

    res[0] = atof(av[1]);
    res[1] = atof(av[2]);
    parser(ac, av, matrix, res);
    display_matrix(matrix);
    display_result(atof(av[1]), atof(av[2]), res);
}
