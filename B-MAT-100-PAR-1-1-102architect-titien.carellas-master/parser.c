/*
** EPITECH PROJECT, 2021
** parser.c
** File description:
** parse the arguments and find the flags
*/

#include "includes/my.h"

char check_flag(char *str)
{
    if (str[0] != '-')
        return ('e');
    if (str[1] == 't' || str[1] == 'z' || str[1] == 'r' || str[1] == 's')
        return (str[1]);
    return ('e');
}

int parser(int ac, char **av, double *matrix, double *res)
{
    int pos;

    for (pos = 3; pos < ac;) {
        if (check_flag(av[pos]) == 't' && (pos + 3) <= ac) {
            do_translation(pos, av, matrix, res);
            pos += 3;
        }
        if (check_flag(av[pos]) == 'z' && (pos+ 3) <= ac) {
            do_scaling(pos, av, matrix, res);
            pos += 3;
        }
        if (check_flag(av[pos]) == 'r' && (pos + 2) <= ac) {
            do_rotation(pos, av, matrix, res);
            pos += 2;
        }
        if (check_flag(av[pos]) == 's' && (pos + 2) <= ac) {
            do_reflection(pos, av, matrix, res);
            pos += 2;
        }
        else
            return (84);
    }
    return (0);
}
