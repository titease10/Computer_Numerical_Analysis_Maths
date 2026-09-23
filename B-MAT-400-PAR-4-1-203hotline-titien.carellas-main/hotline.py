#!/usr/bin/env python3

import  sys
import  math
import  time
def     man_help():
    print("USAGE\n\t./203hotline [n k | d]\n\nDESCRIPTION")
    print("\tn\tn value for the computation of (n k)")
    print("\tk\tk value for the computation of (n k)")
    print("\td\taverage duration of calls (in seconds)")

def     get_number(char):
    if char.isdigit():
        nbr = int(char)
        return nbr
    else:
        sys.stderr.write("Invalid value, a number bigger than 50 is required\n")
        exit(84)

def     get_binomial_coef(n, k):
    return math.factorial(n) // (math.factorial(k) * math.factorial(n - k))


def     print_binomial_distribution():
    n = 3500
    working_hours = 60 * 60 * 8
    phone_number = 25
    p = computation / (working_hours)
    start = time.time()
    overload = 0
    print("Binomial distribution:")
    for i in range(51):
        result = get_binomial_coef(n, i) * (p ** i) * ((1 - p) ** (n - i))
        print("%d -> %.3f" % (i, result), end='')
        if i > phone_number:
            overload += result
        if (i + 1) % 5 == 0 or i == 50:
            print(end='\n')
        else:
            print(end='\t')
    if computation > 320:
        overload = 1
    print("Overload: %.1f" % (overload * 100) + "%")
    end = time.time()
    print("computation time: %.2f ms" % ((end - start) * 1000))

def     print_poisson_distribution():
    working_hours = 8 * 60 * 60
    employee_number = 3500
    phone_number = 25
    proba = employee_number * (computation / (working_hours))
    start = time.time()
    overload = 0
    print("\nPoisson distribution:")
    for i in range(51):
        result = math.exp(-proba) * (proba ** i) / math.factorial(i)
        print("%d -> %.3f" % (i, result), end='')
        if i > phone_number:
            overload += result
        if (i + 1) % 5 == 0 or i == 50:
            print(end='\n')
        else:
            print(end='\t')
    if computation > 320:
        overload = 1
    print("Overload: %.1f" % (overload * 100) + "%")
    end = time.time()
    print("computation time: %.2f ms" % ((end - start) * 1000))

def     print_binomial_coef():
    print(str(call) + "-combinations of a set of size " + str(comp) + ":\n%d"
          % (get_binomial_coef(comp, call)))

if len(sys.argv) == 2 and sys.argv[1] == "-h":
    man_help()
    exit(0)
if len(sys.argv) == 2:
    if sys.argv[1] == "-h":
        man_help()
        exit(0)
    else:
        computation = get_number(sys.argv[1])
        print_binomial_distribution()
        print_poisson_distribution()
        exit(0)
elif len(sys.argv) == 3:
    comp = get_number(sys.argv[1])
    call = get_number(sys.argv[2])
    print_binomial_coef()
else:
    sys.stderr.write("Invalid number of argument try: ./202unsold -h\n")
    exit(84)
