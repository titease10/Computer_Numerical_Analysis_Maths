#!/usr/bin/env python3

import sys
from math import sqrt, exp, pi

def     man_help():
    print("USAGE\n\t./205IQ u s [IQ1] [IQ2]\n")
    print("DESCRIPTION\n\tu mean\n\ts standard deviation")
    print("\tIQ1 minimum IQ\n\tIQ2 maximum IQ")

def     get_number(char):
    if char.isdigit():
        nbr = int(char)
        if nbr >= 0 and nbr <= 200:
            return nbr
        else:
            sys.stderr.write("error: a number between 0 and 200 is expected\n")
            exit(84)
    else:
        sys.stderr.write("Invalid value, a number is expected\n")
        exit(84)

def     check_input():
    tab = []
    i = 1
    while (i < len(sys.argv)):
        tab.append(get_number(sys.argv[i]))
        i += 1
    return tab

def first_calcul(x, tab):
    res = (1 / (tab[1] * sqrt(2 * pi))) * exp(-0.5 * pow((tab[0] - x) / tab[1], 2))
    print(x, format(round(res, 5), ".5f"))
    return res

def my_percent(tab, index):
    res = 0.0
    max = tab[len(tab) - 1]
    while (index < max):
        res = res + (1 / (tab[1] * sqrt(2 * pi))) * exp(-0.5 * pow((index - tab[0]) / tab[1], 2))
        index = index + 0.01
    return res

def iq(tab):
    x = 0
    if len(tab) == 2:
        while (x <= 200):
            first_calcul(x, tab)
            x += 1
    elif len(tab) == 3:
        res = my_percent(tab, 0.0)
        print (format(res, ".1f"), "% of people have an IQ inferior to ", tab[2], sep="")
    elif len(tab) == 4:
        res = my_percent(tab, tab[2])
        print (format(res, ".1f"), "% of people have an IQ between ", tab[2]," and ", tab[3], sep="")

if len(sys.argv) == 2 and sys.argv[1] == "-h":
    man_help()
    exit(0)
elif len(sys.argv) >= 3 and len(sys.argv) <= 5:
    tab_args = check_input()
    iq(tab_args)
    sys.exit(0)
else:
    sys.stderr.write("Invalid number of argument try: ./205IQ -h\n")
    exit(84)
