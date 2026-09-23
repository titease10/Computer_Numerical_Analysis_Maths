#!/usr/bin/env python3

import sys
from math import sqrt, exp, pi

def     man_help():
    print("USAGE\n\t./206neutrinos n a h sd\n\nDESCRIPTION")
    print("\tn number of values\n\ta arithmetic mean")
    print("\th harmonic mean\n\tsd standard deviation")

def     get_number(char):
    if char.isdigit():
        nbr = int(char)
        if nbr >= 0:
            return nbr
        else:
            sys.stderr.write("error: a number biggest than 0 is expected\n")
            exit(84)
    else:
        sys.stderr.write("Invalid value, a number is expected\n")
        exit(84)

def     error_handling():
    tab = []
    i = 1
    while (i < len(sys.argv)):
        tab.append(get_number(sys.argv[i]))
        i += 1
    return tab

def     check_float(string):
    parts = string.split('.')
    if len(parts) > 2:
        return False
    elif len(parts) == 2:
        return parts[0].isdigit() and parts[1].isdigit()
    else:
        return parts[0].isdigit()

def check_input():
    input_val = input("Enter next value: ")
    if input_val == "END":
        return -1
    if check_float(input_val) == True:
        ma = float(input_val)
        if ma < 0:
            exit(84)
        return ma
    else:
        sys.stderr.write("error: a number is expected\n")
        exit(84)

#nb_val -> tab[0], a -> tab[1], h -> tab[2], sd -> tab[3]
def my_calcul(tab, ma):
    total = tab[1] * tab[0]
    temp = (tab[3] * tab[3] + tab[1] * tab[1]) * tab[0]
    tab[0] = tab[0] + 1
    tab[1] = (total + ma) / tab[0]                 #tab[0] = 0 div par 0 interdite
    tab[3] = sqrt(((temp + pow(ma, 2)) / tab[0]) - pow(tab[1], 2))
    tab[2] = tab[0] / ((1 / ma) + ((tab[0] - 1) / tab[2]))   #tab[2] = 0 div par 0 interdite
    return tab

def print_funct(tab, mean_square):
    print ("\tNumber of values:\t%d" % tab[0])
    print ("\tStandard deviation:\t%.2f" % tab[3])
    print ("\tArithmetic mean:\t%.2f" % tab[1])
    print ("\tRoot mean square:\t%.2f" % mean_square)
    print ("\tHarmonic mean:\t%.2f\n" % tab[2])

def my_neutrinos(tab):
    ma = check_input()
    while ma != -1:
        temp = (tab[3] * tab[3] + tab[1] * tab[1]) * tab[0]
        my_calcul(tab, ma)
        mean_square = sqrt((temp + pow(ma, 2)) / tab[0])    # tab[0] = 0 div par 0 interdite
        print_funct(tab, mean_square)
        ma = check_input()
    exit(0)

if len(sys.argv) == 2 and sys.argv[1] == "-h":
    man_help()
    exit(0)
elif len(sys.argv) == 5:
    tab_args = error_handling()
    my_neutrinos(tab_args)
    sys.exit(0)
else:
    sys.stderr.write("Invalid number of argument try: ./205IQ -h\n")
    exit(84)
