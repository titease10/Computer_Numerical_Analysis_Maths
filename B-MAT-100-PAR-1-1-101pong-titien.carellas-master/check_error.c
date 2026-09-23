/*
** EPITECH PROJECT, 2021
** check_error.c
** File description:
** check for errors
*/

#include <stdlib.h>

static int check_numbers(char *nb)
{
    for (int i = 0; nb[i] != '\0'; i++)
        if ((nb[i] < '0' || nb[i] > '9') && nb[i] != '.' && nb[i] != '-')
            return (84);
    return (0);
}
static int check_time_shift(char *nb)
{
    for (int i = 0; nb[i]; i++) {
        if (nb[i] < '0' || nb[i] > '9')
            return (84);
    }
    return (0);
}

int verif_arg(int argc, char **argv)
{
    if (argc != 8)
        return (84);
    for (int i = 1; i != 7; i++)
        if (check_numbers(argv[i]) == 84)
            return (84);
    if (check_time_shift(argv[7]) == 84)
        return (84);
    if (atoi(argv[7]) <= 0)
        return (84);
    return (0);
}
