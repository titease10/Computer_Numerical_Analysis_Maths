/*
** EPITECH PROJECT, 2021
** get_determinant
** File description:
** get the determinant of the matrix
*/

#include "../include/my.h"

static float get_big_det(cipher_t *cipher)
{
    float det;

    det = cipher->key[0]
	* (cipher->key[4] * cipher->key[8]
	- cipher->key[5] * cipher->key[7])
	- cipher->key[3] * (cipher->key[1]
	* cipher->key[8] - cipher->key[2]
	* cipher->key[7]) + cipher->key[6]
	* (cipher->key[1] * cipher->key[5]
	- cipher->key[2] * cipher->key[4]);
	return (det);
}

float get_determinant(cipher_t *cipher)
{
    float det;

    if (cipher->key_len == 4)
        det = (cipher->key[0] * cipher->key[3]) -
            (cipher->key[1] * cipher->key[2]);
    if (cipher->key_len == 9)
        det = get_big_det(cipher);
    return (det);
}
