# ~/pset6/crack
# crack.py
# pset6 cs50
# onelmv
# 12.28.2018
# cracking password

import sys
from crypt import crypt
from cs50 import get_string

if len(sys.argv) == 2:

    # Dictionary
    dic = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
           'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
           'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
           'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
           'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
           'Y', 'Z']

    # hash and salt
    h = sys.argv[1]
    salt = h[:2]

    # Cycle with 1 character word
    for i in dic:
        # checking if my hash is equal to the argument's hash
        if crypt(i, salt) == h:
            print(i)
            exit(0)

    # Cycle with 2 character word
    for i in dic:
        for j in dic:
            word = i + j
            if crypt(word, salt) == h:
                print(word)
                exit(0)

    # Cycle with 3 character word
    for i in dic:
        for j in dic:
            for k in dic:
                word = i + j + k
                if crypt(word, salt) == h:
                    print(word)
                    exit(0)

    # cycle with 4 character word
    for i in dic:
        for j in dic:
            for k in dic:
                for l in dic:
                    word = i + j + k + l
                    if crypt(word, salt) == h:
                        print(word)
                        exit(0)
else:
    print("Usage: ./crack hash")
    exit(1)