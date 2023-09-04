# TODO
import sys
import math

# Luhn reversal function
# Reverse numbers, multiply odds with 2 then sum those
# Add the sum to the sum of remaining (even) numbers
# If last digit (or num modulo 10) is 0, credit card is valid


def luhn_reversals(num):
    # Convert to string so I can work with string functions and reverse it
    n = str(num)[::-1]
    # Odds multiplied by 2
    values = str()
    for odd in n[1::2]:
        values += str(int(odd)*2)
    # Add evens to odds
    for even in n[::2]:
        values += even
    # Sum all values
    sum = 0
    for value in values:
        sum += int(value)

    return sum

# Get user input
card_num = int(input("Enter card number: "))
# Calculate card number's Luhn result
luhn_result = luhn_reversals(card_num)

# Validation
card_num_lenght = len(str(card_num))
if card_num_lenght not in range(13, 17) or (luhn_result % 10) != 0:
    print("INVALID")
    sys.exit()

# Check card vendor by examing first two digits
first_two = int(str(card_num)[:2])
if first_two == 34 or first_two == 37:
    print("AMEX")
elif first_two in range(50, 56):
    print("MASTERCARD")
elif (math.floor(first_two / 10)) == 4:
    print("VISA")
else:
    print("INVALID")