# ~/ pset1/mario/less/
# pset6 cs50
# onelmv
# 12.22.018
# Print a half-pyramid from 0 to 23 steps.

from cs50 import get_int

# ask to user for a number between 1 and 23
while True:
    h = get_int("Height: ")

    # cheking the user value
    if h >= 0 and h <= 23:
        break

# printing a halph pyramid
for i in range(h):
    # printing spaces
    print(" " * (h - i - 1), end="")
    # printing #
    print("#" * (i + 2), end="")
    # new line
    print()
