# TODO
# Prompt user for input with validation 1-8

while True:
    try:
        rows = int(input("Height [1-8]: "))
        if rows in range(1, 9):
            break
    except:
        print("Enter number between 1 and 8.")

for row in range(1, rows + 1):
    # print(" " * (rows - row),"#" * row," ","#" * row)
    print(" " * (rows - row), end="")
    print("#" * row, end="  ")
    print("#" * row)