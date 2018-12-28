# ~/pset6/caesar
# caesar.py
# pset6 cs50
# onelmv
# 12.26.2018
# Caesar cypher

import sys
from cs50 import get_string

# cheking the argument exist
if len(sys.argv) == 2:

    # checking if the argument it's a number
    if sys.argv[1].isdigit():

        # converting the key (str -> int)
        key = int((sys.argv[1]))

        # Taking text from the user
        text = get_string("plaintext: ")

        # print tag
        print("ciphertext: ", end="")
        for i in text:
            # encripting only the alpha character
            if i.isalpha():
                # Checking if the char is Upper or lower case
                if i.isupper():
                    # encrypting and printing
                    # ord() convert to int, and chr convert to str again
                    print(chr((ord(i) - 65 + key) % 26 + 65), end="")
                else:  # i.islower()
                    # encrypting and printing
                    print(chr((ord(i) - 97 + key) % 26 + 97), end="")
            #  non-alphabetical characters should be outputted unchanged.
            else:
                print(i, end="")
        print()
    else:
        print("Usage: ./caesar key")
else:
    print("Usage: ./caesar key")
    exit(1)