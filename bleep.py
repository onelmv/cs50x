# ~/pset6/bleep
# bleep.py
# pset6 cs50
# onelmv
# 2.26.2018
# program that censors messages that contain words that appear on a list of supplied "banned words."

from cs50 import get_string
from sys import argv


def main():

    if len(argv) == 2:

        # Diccionaries
        banned_words = set()
        text = set()
        text = get_string("What message would you like to censor?\n").split()

        # Storing each word from the file ,removing "\n"
        file = open(argv[1], 'r')
        for word in file:
            banned_words.add(word.rstrip('\n'))

        # Checking each word and printing
        for word in text:
            if word.lower() in banned_words:
                print(len(word) * "*", end=" ")
            else:
                print(word, end=" ")
        print()

    else:
        print("Usage: bleep.py [diccionary]")
        exit(1)


if __name__ == "__main__":
    main()
