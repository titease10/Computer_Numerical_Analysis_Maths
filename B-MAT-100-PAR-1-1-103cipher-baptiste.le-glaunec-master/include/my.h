/*
** EPITECH PROJECT, 2021
** my.h
** File description:
** header file
*/

#ifndef MY_H_
#define MY_H_

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

typedef struct cipher_s {
    int key_len;
    float *key
} cipher_t;

int get_reverse(cipheer_t *cipher);
float get_determinant(cipher_t *cipher);
int verif_arg(int, char **);

#endif
