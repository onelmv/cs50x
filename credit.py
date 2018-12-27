# ~/pset6/credit
# credit.py
# pset6 cs50
# onelmv
# 12.22.2018
# verification if a credit card number is valid according to Luhn’s algorithm.

from cs50 import get_int
import math

# luhn algorithm function


def luhn_algorithm(card):

    # take numbers in pair's indexs starting by second-to-last digit
    # (storing in reverse)
    sub_list = card[(len(card)-2)::-2]
    sub_list_2 = card[::-2]

    # multiplying by 2 each number
    for i in range(len(sub_list)):
        # store each number multiplied
        n = sub_list[i] * 2

        # if the new number have 2 digit , the two are added.
        if n >= 10:
            sub_list[i] = (n % 10) + (n // 10)
        else:
            sub_list[i] = n

    # adding up each number of the two sub lists
    tmp = sum(sub_list) + sum(sub_list_2)

    # cheking if tmp end in 0
    if(tmp % 10) == 0:
        return True
    else:
        return False

# function for print card name


def name(card, leng):

    if leng == 16:
        if card[0] == 4:
            print("VISA")
        elif card[0] == 5 and (card[1] >= 1 and card[1] <= 5):  # if the 2 first digit are betewn 51 and 55
            print("MASTERCARD")
    elif leng == 13:
        if card[0] == 4:
            print("VISA")
    elif leng == 15:
        if card[0] == 3 and (card[1] == 4 or card[1] == 7):
            print("AMEX")

###################################################################


# promt
while True:
    card = get_int("Card number: ")
    if card >= 0:
        break

# converting the number(card) into a list
num_list = []
for digit in str(card):
    num_list.append(int(digit))

# lenght of th list
leng = len(num_list)

if leng >= 13 and leng <= 16:
    if leng == 14:
        print("INVALID")

    # Luhn’s algorithm.
    elif luhn_algorithm(num_list) == True:
        # printing card names
        name(num_list, leng)

    else:
        print("INVALID")
else:
    print("INVALID")