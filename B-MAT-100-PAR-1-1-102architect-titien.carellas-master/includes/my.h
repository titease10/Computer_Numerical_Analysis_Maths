/*
** EPITECH PROJECT, 2021
** my.h
** File description:
** header file
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

int parser(int ac, char **av, double *matrix, double *res);
void mult_matrix(double *matrix, double *reloaded);
void fill_rot_matrix(double *matrix, double nb);
void fill_ref_matrix(double *matrix, double nb);
void do_translation(int, char **, double *, double *);
void do_scaling(int, char **, double *, double *);
void do_rotation(int, char **, double *, double *);
void do_reflection(int, char **, double *, double *);
void display_result(double, double, double *);
void mult_matrix(double *, double *);
void fill_rot_matrix(double *, double);
void fill_ref_matrix(double *, double);
void display_matrix(double *);

#endif
