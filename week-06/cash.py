# TODO
import cs50

# Quarter = 25 cents
# Dime = 10 cents
# Nickel = 5 cents
# Penny = 1 cent

# Validation
while True:
    try:
        change = cs50.get_float("Change owed: ")
        if change > 0:
            break
    except:
        print("Enter number greater than 0.")

# Convert to cents
cents = round(change * 100)
# Counter for coins
coins_count = 0

# Loop over money, substract coins top to bottom
while cents > 0:
    if cents >= 25:
        coins_count += 1
        cents -= 25
    elif cents >= 10:
        coins_count += 1
        cents -= 10
    elif cents >= 5:
        coins_count += 1
        cents -= 5
    elif cents >= 1:
        coins_count += 1
        cents -= 1

print(coins_count)