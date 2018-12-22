# ~/pset6/cash
# cash.c
# pset6 cs50
# onelmv
# 12.22.2018
# Calculates the minimum number of coins required to give a user change.

from cs50 import get_float

# Coin counter
count = 0

# pront to evaluate input.
while True:
    # input a float < 1
    c = get_float("Change owed: ")

    if c >= 0:
        break

# Rounding value to hundreds
c = round(c * 100)

# Calculating
while c >= 25:
    c -= 25
    count += 1
while c >= 10:
    c -= 10
    count += 1
while c >= 5:
    c -= 5
    count += 1
while c >= 1:
    c -= 1
    count += 1

# printing
print(count)