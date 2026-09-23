/*
** EPITECH PROJECT, 2021
** check_error.c
** File description:
** check for errors
*/

#include <stdlib.h>

static int check_args(int ac)
{
    if (ac < 5)
        return (84);
    return (0);
}

static int check_nb(char *str)
{
    int i = 0;

    for (; str[i] == '-'; i++);
    for (; str[i]; i++)
        if (str[i] < '0' || str[i] > '9')
            return (84);
    return (0);
}

int check_error(int ac, char **av)
{
    if (check_args(ac) == 84)
        return (84);
    if (check_nb(av[1]) == 84 || check_nb(av[2]) == 84)
        return (84);
    else
        return (0);
}
