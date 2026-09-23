/*
** EPITECH PROJECT, 2021
** test_process.c
** File description:
** test the 3 processing functions
*/

#include <criterion/criterion.h>
#include "../includes/struct.h"
#include "../includes/my.h"

Test(test_velocity, basic_test_x)
{
    vector_t vn;
    vector_t v0;
    vector_t needed;
    vector_t res;

    vn = creat_vector("7", "9", "-2");
    v0 = creat_vector("1", "3", "5");
    needed = creat_vector("6", "6", "-7");
    res = calc_velocity(vn, v0);
    cr_assert_eq(res.x, needed.x);
}

Test(test_velocity, basic_test_y)
{
    vector_t vn;
    vector_t v0;
    vector_t needed;
    vector_t res;

    vn = creat_vector("7", "9", "-2");
    v0 = creat_vector("1", "3", "5");
    needed = creat_vector("6", "6", "-7");
    res = calc_velocity(vn, v0);
    cr_assert_eq(res.y, needed.y);
}

Test(test_velocity, basic_test_z)
{
    vector_t vn;
    vector_t v0;
    vector_t needed;
    vector_t res;

    vn = creat_vector("7", "9", "-2");
    v0 = creat_vector("1", "3", "5");
    needed = creat_vector("6", "6", "-7");
    res = calc_velocity(vn, v0);
    cr_assert_eq(res.z, needed.z);
}

Test(test_coordinates, basic_test_x)
{
    vector_t velocity;
    vector_t vn;
    int n = 4;
    vector_t needed;
    vector_t res;

    velocity = creat_vector("6", "6", "-7");
    vn = creat_vector("7", "9", "-2");
    needed = creat_vector("31", "33", "-30");
    res = calc_coordinates(velocity, vn, n);
    cr_assert_eq(res.x, needed.x);
}

Test(test_coordinates, basic_test_y)
{
    vector_t velocity;
    vector_t vn;
    int n = 4;
    vector_t needed;
    vector_t res;

    velocity = creat_vector("6", "6", "-7");
    vn = creat_vector("7", "9", "-2");
    needed = creat_vector("31", "33", "-30");
    res = calc_coordinates(velocity, vn, n);
    cr_assert_eq(res.y, needed.y);
}

Test(test_coordinates, basic_test_z)
{
    vector_t velocity;
    vector_t vn;
    int n = 4;
    vector_t needed;
    vector_t res;

    velocity = creat_vector("6", "6", "-7");
    vn = creat_vector("7", "9", "-2");
    needed = creat_vector("31", "33", "-30");
    res = calc_coordinates(velocity, vn, n);
    cr_assert_eq(res.z, needed.z);
}
