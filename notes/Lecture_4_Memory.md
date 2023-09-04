# Lecture 4 - Memory

## Hexadecimal
Base 16 numbering system.
0 1 2 3 4 5 6 7 8 9 A B C D E F

One hexadecimal digit has 4 bits (F = 1111).

Convention is to prefix all hexadecimal values wiht 0x to avoid confusion with decimal system (0x0 = 0, 0xF = F, etc.).

## Accessing memory

### Operator &
Provide means of getting the address of the memory so it is a reference to an address where the data is stored.
So printing it will return the memory address, not the value itsef.

```c
int n = 50;

// & operand example
printf("%p\n", &n) // returns 0x7ffcc784a04c, address in the memory

```

### Operator *
This is dereference operator, it will get the data stored in the memory.
It's useful when reating pointer variables where it will "read" and store value from some referenced memory address.

### Pointers
Variable which contains memory address of some value.

Example
```c
int n = 50;
int *p = &n; // pointer variable, contains address in memory for value stored in n
            // star * here defines a data type as we declare it
prinf("%p", p) // prints memory oddress of n (0xf334 let's say)
printf("%i", *p) // prints out value stored in that address (50 in this case)
                // star * here defines using a value stored in a referenced memory (usage, not declaratioon of data type)
                // Normaally this would be different symbol but that's how it is in C
returns 50 in this case
```

These are just references, so in C you need to use * operand to pull a value from some value stored in some &variable. So pointers store memory addresses and we use them as references to existing values.

In functions (as they take values as arguments so they make a copy of the variable value, not the reference address), we can reference things in upper scope like this.

Let's consider a simple swap value function which takes number a and b and swaps the so a = b, b = a.

```c
int main()
{
  int x = 10
  int y = 20

  swap(x, y);
  printf("x: %i, y: %i\n", x, y) // prints out x: 10, y: 20

  swap2(&x, &y);
  printf("x: %i, y: %i\n", x, y) // prints out x: 20, y: 10
}
// This won't change anything in the main
void swap(int a, int b)
{
  int tmp = a;
  a = b;
  b = tmp;
}

// This will swap x and y in the main
void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
```

## Strings

In C, everything between "" will be delimited with a null characted, not like char.

So, techicaly, in example below:

string s = "Hi!";

s is just a pointer to the memory of value "H" stored somewher, then it can look between that address and the last delimiting character which will be null. 

So, there is no "string" keyword, this is actually:

char *s = "Hi!";

So "string" is just a CS50 thing, written as a synonim

`typedef char *string;`

**What we do for strings in C? We write char**

```c
char *s = "Hi!";

printf("%s\n", s); // prints the "string", "Hi!"
printf("%p\n", s); // prints the memory address of "H"

// Printf goes from first char reference till cloising null characted
```

## Pinter arithmetics

Cool thing, you can do basic calculus with poitners since in arrays (string is an array basically), chars are stored in memory byte to byte.

```c
char *s = "Hi!";

printf("%c\n", *s); // Prints "H" (char of value stored in s)
printf("%c\n", *(s+1)); //Prints "i" (char of value stored in memory next to s)
printf("%c\n", *(s+2)); //Prints "!" (char of value stored in memory next to s+1)
printf("%c\n", *(s+3)); //Prints blank if memory is blank but allocated, otherwise will be segmentation faults errors

// This is what happening under the hood of square bracket notations (something[n]).

// We can print it as string, not char like this
printf("%s\n", s); // Prints "Hi!" (whole string
printf("%s\n", s+1); //Prints "i!" (rest of string next to s[0])
printf("%s\n", s+2); //Prints "!" (rest of string next to s[1])
```

## Malloc & Free

**Malloc** is a function to reserve specific amout of memory. It returns the address of the first byte of reserved memory but does not have a null termination so you need to handle the memory yourself.

If it returns NULL, probably memory was exceded and it can crash. So good thing is to have a validation which checks if NULL was returned and if yes, exit.

**Free** does the oposite - you feed it an memory address and it frees it. Good practice is to free memory when done after malloc.

Both need stdlib.h library to use them.

Example: copy a variable's value
```c
// Initial string I get from user
char *s = get_string("s: ");
// One I wanna copy
char *t = malloc(strlen(s)+1); // This is now a blank chunk of memory sized sufficiently to house *s

// To make a copy, I need a for loop to do each char
for (int i = 0; i < strlen(s) + 1; i++)
{
  // strlen(s) + 1 goes one char over original string just to copy a null char as string needs it
  t[i] = s[i]
}

// Once done, free the memory
free(t);

```

Example: malloc with array
```c
 int *x = malloc(3 * sizeof(int));
 
 // Same as 

 int x[3];

```

## NUL VS NULL

NUL is a "\0", nul character. String are delimited by it.

NULL is a pointer to address 0, meaning zero.

## Valgrind

Debuger for bugs with memory.

Usage: call it on already compiled c program ($ valgrind ./yourprogram)

It will return sort of statistics about the memory usage.
Leaks will probably mean free was not used after malloc.

## Garbage values
Leftovers in memory, values you can stumble upon if your arrays are not initialized with values.

Example
```c
int nums[1024];

for (int i = 0; i < 1024; i++)
{
  printf("%i\n", nums[i]);
  // This will print 0 as C will zero out most of things but some things will be random numbers. Those are garbage values
}

```

## Scope in C
If we are to look the memory utilization by C, we have machine code and globals "on top", then heap as a available allocation during execution from one direction, then stack goes from different direction.

So:
Machine code
Globals - things outside of the main function
Heap - free memory available for allocation to C
 ↓
 ↓

 ↑
 ↑
Stack - functions


Stack startis with main, then goes "upwards"

↑
Function 1
↑
Main

**Stack overflow** then overflows the stack and **heap overflow** overflows the heap. In both cases, I'm touching memory I should not touch so we say buffer overflow. 