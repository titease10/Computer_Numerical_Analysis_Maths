/*
** EPITECH PROJECT, 2021
** process.c
** File description:
** process the function
*/

#include "math.h"
#include "includes/struct.h"

vector_t calc_velocity(vector_t vn, vector_t v0)
{
    vector_t result;

    result.x = vn.x - v0.x;
    result.y = vn.y - v0.y;
    result.z = vn.z - v0.z;
    return (result);
}

vector_t calc_coordinates(vector_t velocity, vector_t vn, int n)
{
    vector_t result;

    result.x = vn.x + (velocity.x * n);
    result.y = vn.y + (velocity.y * n);
    result.z = vn.z + (velocity.z * n);
    return (result);
}

float norm_vec(vector_t v1)
{
    float x = v1.x * v1.x;
    float y = v1.y * v1.y;
    float z = v1.z * v1.z;

    return (sqrt(x + y + z));
}

float calc_angle(vector_t vec)
{
    float norme = norm_vec(vec);
    float angle = acos(vec.z/norme) * (180 / M_PI) - 90;

    return (angle);
}

int verif_touch(vector_t v2, vector_t vel)
{
    float norm = norm_vec(vel);

    if ((v2.z >= 0 && vel.z < 0) || (v2.z <= 0 && vel.z > 0)) {
        if (norm > 0)
            return (0);
    }
    return (84);
}
