/*
** EPITECH PROJECT, 2021
** reverse_key.c
** File description:
** reverse the key matrix
*/

#include "../include/my.h"

static void reverse_key_4(cipher_t *cipher, float det)
{
    float *key = malloc(sizeof(float) * 4);

    key[0] = cipher->key[3] / det;
    key[1] = (-1 * cipher->key[1]) / det;
    key[2] = (-1 * cipher->key[2]) / det;
    key[3] = cipher->key[0] / det;
    cipher->reversed_key = key;
}

static void reverse_key_9(cipher_t *cipher, float det)
{
    float *key = malloc(sizeof(float) * 9);

    key[0] = (cipher->key[4] * cipher->key[8]
              - cipher->key[5] * cipher->key[7]) / det;
    key[1] = -1 * (cipher->key[1] * cipher->key[8]
              - cipher->key[2] * cipher->key[7]) / det;
    key[2] = (cipher->key[1] * cipher->key[5]
              - cipher->key[2] * cipher->key[4]) / det;
    key[3] = -1 * (cipher->key[3] * cipher->key[8]
              - cipher->key[5] * cipher->key[6]) / det;
    key[4] = (cipher->key[0] * cipher->key[8]
              - cipher->key[2] * cipher->key[6]) / det;
    key[5] = -1 * (cipher->key[0] * cipher->key[5]
              - cipher->key[2] * cipher->key[3]) / det;
    key[6] = (cipher->key[3] * cipher->key[7]
              - cipher->key[4] * cipher->key[6]) / det;
    key[7] = -1 * (cipher->key[0] * cipher->key[7]
              - cipher->key[1] * cipher->key[6]) / det;
    key[8] = (cipher->key[0] * cipher->key[4]
              - cipher->key[1] * cipher->key[3]) / det;
    cipher->reversed_key = key;
}

int get_reverse(cipher_t *cipher)
{
    float det = get_determinant(cipher);

    if (det == 0)
        return (84);
    if (cipher->key_len == 4) {
        reverse_key_4(cipher, det);
        return (0);
    }
    if (cipher->key_len == 9)
        reverse_key_9(cipher, det);
    return (0);
}
