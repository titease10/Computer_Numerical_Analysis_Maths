/*
** EPITECH PROJECT, 2021
** test_check_error.c
** File description:
** unit tests
*/

#include <criterion/criterion.h>
#include "../includes/my.h"

Test(check_error, incorrect_numbers)
{
    int ac = 8;
    char **av = malloc(sizeof(char *) * 8);
    int result = 0;

    av[0] = "abc";
    av[1] = "DEF";
    av[2] = "..";
    av[3] = "-1";
    av[4] = "-1";
    av[5] = "-1";
    av[6] = "-1";
    av[7] = "1";
    result = verif_arg(ac, av);
    cr_assert_eq(result, 84);
}

Test(check_error, correct_numbers)
{
    int ac = 8;
    char **av = malloc(sizeof(char *) * 8);
    int result = 0;

    av[0] = "-1";
    av[1] = "-1";
    av[2] = "-1";
    av[3] = "-1";
    av[4] = "-1";
    av[5] = "-1";
    av[6] = "-1";
    av[7] = "1";
    result = verif_arg(ac, av);
    cr_assert_eq(result, 0);
}

Test(check_error, float_time_shift)
{
    int ac = 8;
    char **av = malloc(sizeof(char *) * 8);
    int result = 0;

    av[0] = "-1";
    av[1] = "-1";
    av[2] = "-1";
    av[3] = "-1";
    av[4] = "-1";
    av[5] = "-1";
    av[6] = "-1";
    av[7] = "1.1";
    result = verif_arg(ac, av);
    cr_assert_eq(result, 84);
}

Test(check_error, correct_time_shift)
{
    int ac = 8;
    char **av = malloc(sizeof(char *) * 8);
    int result = 0;

    av[0] = "-1";
    av[1] = "-1";
    av[2] = "-1";
    av[3] = "-1";
    av[4] = "-1";
    av[5] = "-1";
    av[6] = "-1";
    av[7] = "1";
    result = verif_arg(ac, av);
    cr_assert_eq(result, 0);
}

Test(check_error, one_argument)
{
    int ac = 1;
    char **av = malloc(sizeof(char *));
    int result = 0;

    av[0] = "toto";
    result = verif_arg(ac, av);
    cr_assert_eq(result, 84);
}

Test(check_error, negative_time_shift)
{
    int ac = 8;
    char **av = malloc(sizeof(char *) * 8);
    int result = 0;

    av[0] = "-1";
    av[1] = "-1";
    av[2] = "-1";
    av[3] = "-1";
    av[4] = "-1";
    av[5] = "-1";
    av[6] = "-1";
    av[7] = "-1";
    result = verif_arg(ac, av);
    cr_assert_eq(result, 84);
}
