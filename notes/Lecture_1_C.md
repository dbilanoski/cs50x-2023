# Lecture 1 - C

## Intro

Source code - code we are writing as programmers (high level code).
Machine code - code computers understand and executes (low level code, binary, etc.)

Compilers - convert source code to machine code so the program is executed.
Flow: Source code -> compiler -> machine code

Things to have in mind when programming:
  * Correctness
  * Design
  * Style


## Basics of C

### Compiling and running C programs

Hello world example in C language

```c

#include <sdio.h>

int main(void)
{
  printf("Hello, world\n");
}

```

To compile, execute:

```bash

make hello

```
That will crate file called hello or return errors if c file has issues.

To run compiled program, execute new hello file.

```bash

./ hello

```

### CS50.h

Library with custom function the course is gonna teach at the beginning to make C easier.


## Basics of C

### Data types

char - single character, use single quotes for enclosure
string - text more than 1 character, use double quotes for enclosure
int - integer, number, limit is aroud -2 billion and 2 billions as those are 32bits (otherwise interger overflow occurs)
long - integers with more bits so they support longer numbers
float - decimal numbers
double - bigger decimal numbers

### Operators

* = means assigment
* == means equality
* ">" means greater than
* "<" means less than
* || means or
* && means and
* Basic mathematical operators as ususal


### Variables
They are strict and need to be stated what type of data it is (number, string, boolean etc.) on initialization.

```c
string example = "Some example variable contens";
```
#### Format codes

* %c - chars
* %s - strings
* %i - integers
* %li - long integers
* %f - floats

### Conditionals

Curly braces are not technicaly needed, it's matter of style agreed upon.

Condition statement in C example

```c
if (x < y)
{

/* Some code */
printf("x is less than y\n");

}
else if
{
  /* Some code */
  printf("some other code\n");
}
else
{
  printf("some other code\n");
}
```

### Loops

Counter variable syntax example
```c
counter = counter + 1;
counter += 1;
cunter ++;

/* All three increment by 1 */
```
#### While Loop

```c
int counter = 1;
while (counter <= 3)
{
  printf("count three times %d\n", counter);
  counter ++;
}
```

#### Do..while loop

```c
int userInput;
do 
{
  userInput = getInt("Enter number greater than 0: ");
} while ( userInput < 0 );

```

Forever loop example
```c
#include <stdbool.h> /* Needs stdbool.h library to use special boolean keys */
while (true)
{
  /* some code which will run forever*/
}

while (1)
{
  /* some code which will run forever also as 1 equals to true*/
}
```

#### For Loop

```c
for (int i = 1; i <= 3; i++)
{
  printf("count three times %d\n", i);

}
```

### Functions

int main(void) would be the main function inside which we are putting all the code for the program.
Any custom function we wanna write ourselves:
  * Either goes to the begining of the file (bad practice)
  * or we define blank functions at the top (after includes), then write those at the end.

Reason is that C goes from top to bottom and does not "know" functions defined after the main() before it reaches those.

#### Example: Printing the grid

This one asks the user about the grid side (n) and prints it in a manner n x n.

If n = 2

Expected behavior

| ? | | ? |

| ? | | ? |


```c

// Our includes (importing libraries)
#include <stdio.h>
#include <cs50.h>

// Our blank functions we were writing after the main function
int get_size(void);
void print_grid(int size);

// Our main fuction
int main(void)
{

    // Ask user for number of block and rows in grid
    int n = get_size();


    // Draw rows n_bricks x n_bricks
    print_grid(n);

}


// Our custom functions

int get_size(void)
{
    int n;

    do
    {
        n = get_int("Size: ");
    }

    while (n <= 0 || n > 10);
    return n;
}


void print_grid(int size)
{
     for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            printf("| ? | ");
        }
        printf("\n");
    }
}


```


## References

1. [CS50 C Man Page](https://manual.cs50.io/)
