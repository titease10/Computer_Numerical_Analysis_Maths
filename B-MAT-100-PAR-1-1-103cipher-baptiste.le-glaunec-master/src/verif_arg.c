/*
** EPITECH PROJECT, 2021
** verif_argc.c
** File description:
** verif_argc
*/

#include "../include/my.h"

void put_h(void)
{
    printf("USAGE\n    ./103cipher message key flag\n\nDESCRIPTION\n    messa");
    printf("ge     a message, made of ASCII characters\n    key         the ");
    printf("encryption key, made of ASCII characters\n    flag        0 for ");
    printf("the message to be encrypted, 1 to be decrypted\n");
}

int verif_arg(int argc, char **argv)
{
    if (strcmp(argv[1], "-h") == 0) {
        put_h();
        return (0);
    }
    if (argc != 4)
        return (84);
    if (atoi(argv[3]) != 1 && atoi(argv[3]) != 0)
        return (84);
    return (0);
}
