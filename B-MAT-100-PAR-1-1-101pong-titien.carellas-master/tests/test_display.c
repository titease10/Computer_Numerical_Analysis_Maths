/*
** EPITECH PROJECT, 2021
** test_display.c
** File description:
** unit tests
*/

#include  <criterion/criterion.h>
#include  <criterion/redirect.h>
#include "../includes/my.h"
#include "../includes/struct.h"

void  redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(display_velocity, simple_vec, .init = redirect_all_std)
{
    vector_t vel = creat_vector("12", "12", "12");

    display_velocity(vel);
    fflush(stdout);
    cr_expect_stdout_eq_str("The velocity vector of the ball is:\n(12.00, 12.00, 12.00)\n");
}

Test(display_coordinates, simple_vec, .init = redirect_all_std)
{
    vector_t vel = creat_vector("12", "12", "12");

    display_coordinates(vel, 3);
    fflush(stdout);
    cr_expect_stdout_eq_str("At time t + 3, ball coordinates will be:\n(12.00, 12.00, 12.00)\n");
}

Test(display_angle, simple_vec, .init = redirect_all_std)
{
    display_angle(12);
    fflush(stdout);
    cr_expect_stdout_eq_str("The incidence angle is:\n12.00 degrees\n");
}
