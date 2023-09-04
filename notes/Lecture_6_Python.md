# Week 6 - Python

* Modern high level language
* Interpreted by the Python program, top to bottom left to right
* Dynamically typed
* Easier on the syntax
* Syntax is nested, curly braces not needed

Float point imprecision is still a thing so division will return incorrectly on bigger digit floating points.
Integer overflow is not an issue in Python.

## Documentation
https://docs.python.org/3/c-api/index.html

## Variables
```python
counter = 0
counter += 1
```

Variables are of wider scope so once declared even inside of loops can be used ouside of those.

## If statement

```python
if x < y:
    print("x is less than y")
elif x > y:
    print("y is less than x")
else:
    print("something else")
```


## Loops

```python
# While loop
i = 0
while i < 3:
  print("meow")
  i += 1

# For loop (we use range for how many digis to loop over)
for i in range(3):
  print("meow")

# Infinite loop
while True
  print("meow")
```

## Functions

```python

def meow(n)
  for i in range(n):
    print("meow")

meow(3)

# Result: meow (3 x)
```

## Examples

Calculator
```python
# Taking user input with input() always retruns strings so we convert it to integers using int()
x = int(input("x: "))
y = int(input("y: "))

print(x + y)
```

Validating user input
```python
# We are repeating the user input prompt until user inputs a number larger than 0
# We are using try - in case user enters a string this way we are catching the error and staying in the loop
while True:
  try:
    n = int(input("Height: "))
    if n > 0:
      break
  except ValueError:
    print("Enter a number greater than 0.")
``` 

Dictionary (dict example)
```python
people = dict() # or just {}

people["Carter"] = "+1-617-495-100";
people["David"] = "+1-527-665-250";

# Get user input
name = input("Name: ")

# Return corresponding value with name
if name in people:
  print(f"Number: {people[name]}")
else
  print(f"{name} does not exist in this dictionary")
```

Compare strings
```python
# Get two strings from user
s = input("s: ")
t = input("t: ")

# Compare them
if s == t:
  print("Same")
else:
  print("Differents")

# Takeout from this in relation to C - python compares values, not memory addresses.
```

Write to CSV
```python
import csv # importing csv libary

# Open file
file = open("phonebook.csv", "a") # append mode

# Get name and number from user
name = input("Name: ")
number = input("Number: ")

# Initialize writing function on that file to a variable
# writer = csv.writer(file)

# Write one row as a list to the csv
#writer.writerow([name, number]) 

# Better version
writer = csv.DictWriter(file, fieldnames=["name", "number"])
  # This way swapping collumns in the csv does not matter as the method will check field names
writer.writerow({"name": name, "number": number})

# Close the file
file.close()
```
