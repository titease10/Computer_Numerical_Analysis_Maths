#!/usr/bin/env python3

import  sys
import  math

def     man_help():
    print("USAGE")
    print("\t./204ducks a\n")
    print("DESCRIPTION")
    print("\ta\tconstant (between 0 and 2.5)")

def     check_float(string):
    parts = string.split('.')
    if len(parts) > 2:
        return False
    elif len(parts) == 2:
        return parts[0].isdigit() and parts[1].isdigit()
    else:
        return parts[0].isdigit()

def     get_number(string):
    if check_float(string) == True:
        nbr = float(string)
        if nbr >= 0 and nbr <= 2.5:
            return nbr
        else:
            sys.stderr.write("error: a number between 0 and 2.5 is expected\n")
            exit(84)
    else:
        sys.stderr.write("error: a number between 0 and 2.5 is expected\n")
        exit(84)

def     get_proba(a, t, mode = 0):
    if mode == 0:
        return -a * math.exp(-t) - (4 - 3 * a) / 2 * math.exp(-2 * t) - (2 * a - 4) / 4 * math.exp(-4 * t)
    else:
        return a * math.exp(-t) + (4 - 3 * a) * math.exp(-2 * t) + (2 * a - 4) * math.exp(-4 * t)

def     get_average_time(a):
    result = float(0)
    t = float(0)
    while t < 10:
        result += get_proba(a, t, 1) * t / 1000
        t += 0.001
    return result

def     get_standard_deviation(a, average_time):
    result = float(0)
    t = float(0)
    while t < 100:
        result += pow(t - average_time, 2) * get_proba(a, t, 1) / 1000
        t += 0.001
    result = math.sqrt(result)
    return result

def     get_come_back(a, percent):
    t = 0.0
    while t < 1000:
        if get_proba(a, t / 60) - get_proba(a, 0) >= percent:
            return t
        t += 0.002
    raise ValueError("This gonna too far...")

def     print_result(a):
    print("Average return time: " + str(int(get_average_time(a)))
          + "m " + "%ds" % math.ceil((get_average_time(a) - int(get_average_time(a))) * 60))
    print("Standard deviation:  %.3f" % get_standard_deviation(a, get_average_time(a)))
    print("Time after which 50%% of the ducks are back: %dm %d%ds"
          % (get_come_back(a, 0.5) / 60, get_come_back(a, 0.5) % 60 / 10, get_come_back(a, 0.5) % 10))
    print("Time after which 99%% of the ducks are back: %dm %d%ds"
          % (get_come_back(a, 0.99) / 60, get_come_back(a, 0.99) % 60 / 10, get_come_back(a, 0.99) % 10))
    print("Percentage of ducks back after 1 minute: %.1f%%" % ((get_proba(a, 1) - get_proba(a, 0)) * 100))
    print("Percentage of ducks back after 2 minutes: %.1f%%" % ((get_proba(a, 2) - get_proba(a, 0)) * 100))

if len(sys.argv) == 2:
    if sys.argv[1] == "-h":
        man_help()
        exit(0)
    else:
        print_result(get_number(sys.argv[1]))
        exit(0)
else:
    sys.stderr.write("Invalid number of argument try: ./204ducks -h\n")
    exit(84)