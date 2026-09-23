#!/usr/bin/env python3

import sys
from math import pow, sqrt, factorial

distribution = [
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [.00, .02, .06, .15, .27, .45, .71, 1.07, 1.64, 2.71, 3.84, 5.41, 6.63],
    [.02, .21, .45, .71, 1.02, 1.39, 1.83, 2.41, 3.22, 4.61, 5.99, 7.82, 9.21],
    [.11, .58, 1.01, 1.42, 1.87, 2.37, 2.95, 3.66, 4.64, 6.25, 7.81, 9.84, 11.34],
    [.30, 1.06, 1.65, 2.19, 2.75, 3.36, 4.04, 4.88, 5.99, 7.78, 9.49, 9.84, 11.34],
    [.55, 1.61, 2.34, 3.00, 3.66, 4.35, 5.13, 6.06, 7.29, 9.24, 11.07, 11.67, 13.28],
    [.7, 2.20, 3.07, 3.83, 4.57, 5.35, 6.21, 7.23, 8.56, 10.64, 12.59, 15.03, 16.81],
    [1.24, 2.83, 3.82, 4.67, 5.49, 6.35, 7.28, 8.38, 9.80, 12.02, 14.07, 16.62, 18.48],
    [1.65, 3.49, 4.59, 5.53, 6.42, 7.34, 8.35, 9.52, 11.03, 13.36, 15.51, 18.17, 20.09],
    [2.09, 4.17, 5.38, 6.39, 7.63, 8.34, 9.41, 10.66, 12.24, 14.68, 16.92, 19.68, 21.67],
    [2.56, 4.87, 6.18, 7.27, 8.30, 9.34, 10.47, 11.78, 13.44, 15.99, 18.31, 21.16, 23.21]]
fit_validity = ""
offset_right = 0
offset_left = 0
sum_square = 0
probability = 0
sort_param = []
freedom_degree = 0
result = list()
tab = list()
tmp = list()

def     man_help():
    print('USAGE')
    print('\t./208dowels O0 O1 O2 O3 O4 O5 O6 O7 O8\n')
    print('DESCRIPTION')
    print('\tOi\tsize of the observed class')

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
    arg = []
    sum = 0
    for i in range(1, len(sys.argv)):
        arg.append(get_number(sys.argv[i]))
        sum += get_number(sys.argv[i])
    if sum != 100:
        exit(84)
    return arg

def sortTab(param):
    while param[0] < 10:
        param[0] = param[0] + param[1]
        param.remove(param[1])
        global offset_left
        offset_left += 1
    param.reverse()
    while param[0] < 10:
        param[0] = param[0] + param[1]
        param.remove(param[1])
        global offset_right
        offset_right += 1
    param.reverse()
    return param

def computeValue(param):
    global probability
    global sort_param
    global tmp
    global result
    global freedom_degree
    global sum_square
    global fit_validity
    probability = sum([i * param[i] for i in range(len(param))]) / pow(10, 4)
    param = sortTab(param)
    sort_param = param
    for i in range(8):
        tmp.append((factorial(100) / (factorial(i) * factorial(100 - i))) * 100
            * pow(1 - probability, 100 - i) * pow(probability, i))
    tmp.append(100 - sum(i for i in tmp))
    result.append(sum(tmp[:offset_left + 1]))
    result += (i for i in tmp[offset_left + 1:])
    save = result[len(result) - 1 - offset_right:]
    result = result[:len(result) - 1 - offset_right]
    result.append(sum(i for i in tmp[(len(tmp) - 1 - offset_right):]))
    freedom_degree = len(result) - 2
    sum_square = sum(pow(param[i] - result[i], 2)
        / result[i] for i in range(len(result)))
    if distribution[freedom_degree][0] > sum_square:
        fit_validity = "P>99%"
    else:
        for i in range(len(distribution)):
            if distribution[freedom_degree][i] > sum_square:
                if i == 0:
                    fit_validity = "99% > P > 90%"
                elif i > 0 and i <= 10:
                    fit_validity = str(100 - i * 10) + "% < P < " + str(100 - (i - 1) * 10) + "%"
                else:
                    if i == 10:
                        fit_validity = "5% < P < 2%"
                    elif i == 11:
                        fit_validity = "2% < P < 1%"
                return
        fit_validity = "P < 1%"

def printValue():
    global offset_left
    global offset_right
    print("\tx\t|\t0", end='')
    print("-%d" % offset_left if offset_left > 0 else "", end='')
    for i in range(offset_left + 1, len(sys.argv) - 1 - offset_right):
        print("\t|\t%d" % i, end='')
    print("+\t|\ttotal\n\tOx\t|\t", end='')
    print("\t|\t".join("%d" % i for i in sort_param) + "\t|\t100")
    print("\tTx\t|\t", end='')
    print("\t|\t".join("%.1f" % i for i in result) + "\t|\t100")
    print("Distribution:\t\t\tB(100, %.4f)" % probability)
    print("Chi-squared:\t%.3f" % sum_square)
    print("Degrees of freedom:\t\t%d" % freedom_degree)
    print("Fit validity:\t\t\t%s" % fit_validity)

if len(sys.argv) == 2 and sys.argv[1] == "-h":
    man_help()
    exit(0)
elif len(sys.argv) == 10:
    tab_args = error_handling()
    computeValue(tab_args)
    printValue()
    exit(0)
else:
    sys.stderr.write("Invalid number of argument try: ./208dowels -h\n")
    exit(84)