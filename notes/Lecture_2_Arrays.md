# Lecture 2 - Arrays

## Compilers

Backgroud program which makes your code raeadable by computer (assembly code).

In the code, all includes are called headers which are pointers to library files which during compiling gets added to the code, on top of the document (headers).

### Compiling steps

1. Preprocessing takes care of the includes
2. Compiling converts C code to Assembly language
3. Assembling converts Assembly language if your written C code to binary strings
4. Linking links that with all other includes which were earlier in the headers

Includes (libraries) are structured as two files:
- .h file which has function prototypes
- .c file which has actual code

When we include .h file, .c gets taken into account automatically.

## Debuging

Basic thing is to use printf to see the course of something, especially during loops.

VS Code debugger can also be used.
Inside CS50 workspace, debugger already configured. To use:
1. Click breakpoint on the left of the line number (where to stop the code)
2. Write debug50 ./your-app-
3. Use "Step over" button and watch how to program unveils

## Pipes with compiled C programs

Instead of "void" in main function, we declare artc and collect arguments in argv array
```c
int main(int argc, string argv[])
{
  printf("Arguments are: %s\n", argv[1]);
}
 
// Usage
//$ program argument
// Output: Argunents are: argument
```

```c
// Here we are liminig arguments to 1, else print error message
// arg[0] is not counted, always there

int main(int argc, string argv[])
{
  if (argc == 2)
  {
    printf("Arguments are: %s\n", argv[1]);
  }
  else
  {
    // Print default message
    printf("Please provide only one argument");
  }
}

```

## Exit codes / statuses
Main fuction (int) returns an exit code as number.

Default status is 0 - successful exit, no errors.
By stating `return n` where n is some number, we get custom exit code


## Arrays

```c
int score[3];
// Means create array variable of 3 slots of integer
// or reserve 3 times 4 bytes of memory (each integer is 4 bytes)

// Adding to array
score[0] = 10;
score[1] = 20;
score[2] = 30;

// Accessing the array values
printf("Average: %f\n", (score[0] + score[1] + score[2]) \ float (3));


// Feeding it to function
// Prototype
const int num = 3
float average (int input[]);

float averate(int input[]);
{
  int sum = 0;
  for (int i = 0; i < num; i++)
  {
    sum = sum + input[i];
  }
  return sum / float (N);
}
```

## Strings

String is an array of characters, delimited by "\0" (NUL) under the hood, to be used as a delimiter, which means that string will always take one byte of memory more just for the ending zero as a delimiter.

Some examples in code how to access chars and chars in strings

```c
char c1 = 'H';
char c2 = 'I'; 

printf("%c%c\n", c1, c2);
// This will return: HI

printf("%i %i\n", c1, c2);
// This will return: 72 73(because characters are number under the hood and you can access  them like this)

string s = "HI";
printf("%c%c\n", s[0],s[1]);
// This will return: HI

printf("%i %i\n", s[0],s[1]);
// This will return: 72 73


// Array of arrays
string words[];
words[0] = "Hi";
words[1] = "Bye";

printf("%c%c\n", words[0][0], words[0][1]);
// returns: Hi

printf("%c%c%c\n", words[1][0], words[1][1], words[1][1]);
// returns: Bye
```


### string.h

Library for handling strings.

strlen - function which tells the lenght of the string.


### ctype.h

Library for handling different data types.

Example: lowercase to upper case conversion
```c

int main(void)
{
  string s = "example";
  for (int i = 0; i < strlen(s); i++)
  {
    // We can say if letter between a and z (means lowercase alphabet)
    if (s[i] >= 'a' && s[i] <= 'z')
    {
      // In asci chart, uppercase is always lovercas + 32
      // example uppercase A = 65, lowercase a = 97 
      printf("%c", s[i] - 32);
    }
    else
    {
      printf("%c", s[i]);
    }
  }
}
```

Same example with ctype.h function

```c
#include <ctype.h>

int main(void)
{
  string s = "example";
  for (int i = 0; i < strlen(s); i++)
  {
    printf("%c", toupper(s[i]));
  }
}

// Even better, not to call strlen() on each iteration
or (int i = 0, n = strlen(s); i < n; i++)
  {
    printf("%c", toupper(s[i]));
  }

// We declaring second variable which will calculate the len only once

```

## Cryptography

Cipher is an algorythm in cryptography which encripts the content.
