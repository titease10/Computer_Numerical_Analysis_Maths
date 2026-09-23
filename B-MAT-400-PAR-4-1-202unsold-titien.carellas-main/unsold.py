#!/usr/bin/env python3

import  sys

def     get_number(char):
    if char.isdigit():
        nbr = int(char)
        if nbr <= 50:
            sys.stderr.write("The value is too small, it's need to be bigger than 50\n")
            exit(84)
        else:
            return nbr
    else:
        sys.stderr.write("Invalid value, a number bigger than 50 is required\n")
        exit(84)

def     get_result(x, y, a, b):
    return ((a - x) * (b - y)) / ((5 * a - 150) * (5 * b - 150))

def     get_tab():
    tab = []
    for y in range(1, 6):
        row = []
        for x in range(1, 6):
            result = float(get_result(x * 10, y * 10, a, b))
            row.append(result)
        tab.append(row)
    return tab

def     get_sum_x(i):
    result = 0
    for j in range(5):
        result += tab[i][j]
    return result

def     get_sum_y(j):
    result = 0
    for i in range(5):
        result += tab[i][j]
    return result

def     print_joint_law():
    for i in range(len(tab)):
        print("Y=" + str((1 + i) * 10), end='\t')
        for j in range(len(tab[i])):
            print("%.3f" % tab[i][j], end='\t')
        Y_exp.append(get_sum_x(i))
        print("%.3f" % get_sum_x(i))
    print("X law\t", end='')
    for s in range(len(tab) - 1):
        X_exp.append(get_sum_y(s))
        print("%.3f" % get_sum_y(s), end='\t')
    X_exp.append(get_sum_y(s + 1))
    print("%.3f" % get_sum_y(s + 1) + "\t1.000")

def     print_law():
    for z in range(2, 11):
        summ = 0.0
        for y in range(1, 6):
            for x in range(1, 6):
                if (x + y == z and y < 6):
                    summ += get_result(x * 10, y * 10, a, b)
        print("\t%0.3f" %(summ), end='')
    sys.stdout.write("\n")
def totalx():
    res = 0.0
    for i in range(5):
        res += X_exp[i] * ((i + 1) * 10)
    return res

def totaly():
    res = 0.0
    for i in range(5):
        res += Y_exp[i] * ((i + 1) * 10)
    return res

def expx():
    res = 0.0
    for i in range(5):
        res += ((i + 1) * 10 - totalx()) * ((i + 1) * 10 - totalx()) * X_exp[i]
    return res

def expy():
    res = 0.0
    for i in range(5):
        res += ((i + 1) * 10 - totaly()) * ((i + 1) * 10 - totaly()) * Y_exp[i]
    return res

def print_line():
    print("----------------------------------------", end='')
    print("----------------------------------------")

def print_result():
    print_line()
    print("\tX=10\tX=20\tX=30\tX=40\tX=50\tY law")
    print_joint_law()
    print_line()
    print("z\t20\t30\t40\t50\t60\t70\t80\t90\t100\np(Z=z)", end='')
    print_law()
    print_line()
    print("expected value of X:\t" + "%0.1f" %(totalx()))
    print("variance of X:\t\t" + "%0.1f" %(expx()))
    print("expected value of Y:\t" + "%0.1f" %(totaly()))
    print("variance of Y:\t\t" + "%0.1f" %(expy()))
    print("expected value of Z:\t" + "%0.1f" %(totalx() + totaly()))
    print("variance of Z:\t\t" + "%0.1f" %(expx() + expy()))
    print_line()

if len(sys.argv) == 2 and sys.argv[1] == "-h":
    man_help()
    exit(0)
elif len(sys.argv) == 3:
    a = get_number(sys.argv[1])
    b = get_number(sys.argv[2])
    tab = get_tab()
    X_exp = []
    Y_exp = []
    print_result()
else:
    sys.stderr.write("Invalid number of argument try: ./202unsold -h\n")
    exit(84)