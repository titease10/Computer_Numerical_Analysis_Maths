#!/usr/bin/env python3

import  sys
import  math

def     help_print():
    print("USAGE\n\t./201yams d1 d2 d3 d4 d5 c\n\nDESCRIPTION")
    print("\td1\tvalue of the first die (0 if not thrown)")
    print("\td2\tvalue of the second die (0 if not thrown)")
    print("\td3\tvalue of the third die (0 if not thrown)")
    print("\td4\tvalue of the fourth die (0 if not thrown)")
    print("\td5\tvalue of the fifth die (0 if not thrown)")
    print("\tc\texpected combination")

def     get_number(char, val_min):
    try:
        nbr = int(char)
    except:
        sys.stderr.write("the dice's result should only be between 1 and 6 (0 if not thrown)\n")
        exit(84)
    if nbr > 6 or nbr < val_min:
        sys.stderr.write("the dice's result should only be between 1 and 6\n")
        exit(84)
    return nbr

def     get_number_apparition(nb, dices):
    apparition = 0
    for i in range(1, 6):
        if dices[i] == nb:
            apparition += 1
    return apparition

def     get_binomial(a, b):
    try:
        result = (math.factorial(a) / (math.factorial(b) * math.factorial(a - b))) * pow((1 / 6), b) * pow((5 / 6), (a - b))
    except:
        sys.stderr.write("Bad get_binomial\n")
        exit(84)
    return result

def     get_result(wanted, number, dices):
    result = 0.0
    apparition = get_number_apparition(number, dices)
    if wanted < apparition:
        result = 1
    else:
        for n in range(wanted - apparition, 6 - apparition):
            result += get_binomial(5 - apparition, n)
    return result * 100

def     count_good_straight(number, dices):
    good = 0
    check = 1
    max = 6

    if number == 6:
        check = 2
        max = 7
    for i in range(check, max):
        for j in range(1, 6):
            if i == dices[j]:
                good += 1
                break
    return good

def     get_straight(number, dices):
    good = count_good_straight(number, dices)
    if good == 5:
        return 100
    return factorial(5 - good) / pow(6, (5 - good)) * 100

def     check_basic_combination(number, combination, dices):
    good_combination = {"three": 3, "four" : 4}
    print("Chances to get a " + str(number) + " " + combination, end='')
    if combination == "pair":
        result = get_result(2, number, dices)
        print(": " + "%.2f" % result + "%")
        return
    for key in good_combination.keys():
        if combination == key:
            result = get_result(good_combination[key], number, dices)
            print("-of-a-kind", end='')
            print(": " + "%.2f" % result + "%")
            return
    if combination == "yams":
        result = get_result(5, number, dices)
        print(": " + "%.2f" % result + "%")
        return
    if combination == "straight":
        result = get_straight(number, dices)
        print(": " + "%.2f" % result + "%")
        return
    sys.stderr.write("invalid combination\n")
    sys.exit (84)

def factorial(nbr):
    res = 1
    if nbr == 0:
        return 1
    for i in range(nbr, 0, -1):
        res *= i
    return res

def combination(k, n):
    fn = factorial(n)
    fk = factorial(k)
    fnk = factorial(n - k)
    return fn / (fk * fnk)

def     get_full(number1, number2, dices):
    if number1 == number2:
        sys.stderr.write("argument of full can't be the same\n")
        sys.exit (84)
    apparition1 = get_number_apparition(number1, dices)
    apparition2 = get_number_apparition(number2, dices)
    if apparition1 > 3:
        apparition1 = 3
    if apparition2 > 2:
        apparition2 = 2
    three = combination(3 - apparition1, 5 - apparition1 - apparition2)
    pair = combination(2 - apparition2, 2 - apparition2)
    result = three * pair / pow(6, 5 - apparition2 - apparition1)
    return result * 100

def     compute_result(arg_comb, dices):
    arg = arg_comb.split('_')
    combination = arg[0]
    if len(arg) == 2:
        number = get_number(arg[1], 1)
        check_basic_combination(number, combination, dices)
    elif len(arg) == 3 and combination == "full":
        number1 = get_number(arg[1], 1)
        number2 = get_number(arg[2], 1)
        result = get_full(number1, number2, dices)
        print("Chances to get a " + str(number1) + " full of " + str(number2) + ": " + "%.2f" % result + "%")
    else:
        sys.stderr.write("invalid combination\n")
        sys.exit (84)

if len(sys.argv) == 2 and sys.argv[1] == "-h":
    help_print()
    exit(0)
elif len(sys.argv) == 7:
    dices = {}
    for i in range(1, 6):
        dices[i] = get_number(sys.argv[i], 0)
    compute_result(sys.argv[6], dices)
    exit (0)
else:
    sys.stderr.write("Invalid number of argument\n")
    exit(84)