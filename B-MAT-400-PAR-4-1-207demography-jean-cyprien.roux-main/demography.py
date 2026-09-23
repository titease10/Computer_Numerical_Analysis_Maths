#!/usr/bin/env python3

import sys
from math import sqrt, exp, pi

def     man_help():
    print("USAGE\n\t./207demography [code]+\n\nDESCRIPTION")
    print("\tcode\tcountry code")

def checkArguments():
    countryList = list()
    if len(sys.argv) < 2:
        print("Invalid number of args")
        exit(84)
    for i in range(1, len(sys.argv)):
        if not sys.argv[i].isupper():
            print("Invalid Argument: upper case as expected")
            exit(84)
        if len(sys.argv[i]) != 3:
            print("Invalid Argument: a length of 3 as expected")
            exit(84)
        countryList.append(sys.argv[i])
    return countryList

if len(sys.argv) == 2 and sys.argv[1] == "-h":
    man_help()
    exit(0)
else:
    checkArguments()
    exit(0)