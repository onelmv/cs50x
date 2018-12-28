# ~/pset6/vinegere
# vinegere.py
# pset6 cs50
# onelmv
# 12.27.2018
# Vinegere cypher.

import sys
from cs50 import get_string

# cheking the argument exist
if len(sys.argv) == 2:

    # checking if the argument are only apha character
    if sys.argv[1].isalpha():

        key = ((sys.argv[1]))
        text = get_string("plaintext: ")

        # print tag
        print("ciphertext: ", end="")

        # encripting
        j = 0  # key's itinirator
        for i in text:
            # encripting only the alpha character (not space and symbols)
            if i.isalpha():
                # Checking if the char is Upper or lower case
                if i.isupper():
                    # encrypting and printing
                    print(chr((ord(i) - 65 + (ord(key[j % len(key)].upper()) - 65)) % 26 + 65), end="")  # WTF O_O but work!
                else:  # i.islower()
                    # encrypting and printing
                    print(chr((ord(i) - 97 + (ord(key[j % len(key)].lower()) - 97)) % 26 + 97), end="")
                j += 1
            #  non-alphabetical characters should be outputted unchanged.
            else:
                print(i, end="")
        print()
    else:
        print("Usage: ./vigenere k")
        exit(1)
else:
    print("Usage: ./vigenere k")
    exit(1)