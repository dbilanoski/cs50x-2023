# Lecture 3 - Algorithms

## Search algorithms

### Linear search
Goes from 0 to end, one by one.
Example is a classic for loop iterating an array.

### Binary search
Goes from the middle, then checks the value and where to go left or right, repeats till it finds the value.

Steps
1. If nothing left to search, value not there
2. If there are values to search, go to the middle
3. Check if middle is > or < then search value, then go left or right accordingly
4. Repeat 1 - 3

Requirements

* **Array needs to be sorted**

## Running time

Big O notation used to express how algorithm is fast (upper bound, how many steps).

Slowest to fastest:

* O(n²)
* O(n log n)
* O(n) - Linear search
* O(log n) - Binary search
* O(1) - fixed finite num of steps which never changes - best performance.


For lower bound (how few steps), we use omega notation.

* Ω(n²)
* Ω(n log n)
* Ω(n)
* Ω(log n)
* Ω(n1)

If algorithm has same upper and lower bound, theta can be used (Θ)

## Structs

Custom composite structure in C where you create sort of a object, collection of variables associated with that object.
This is not a "real" object as C is not object oriented.

Example syntax

```c
// Create construct before main function
typedef struct
{
  string firstName;
  string lastName
}
person;

// Usage
// Create an instance
person people[2]; // say I'm doing array of 2
// Populate array with values
people[0].fistName = "Danilo";
people[0].lastName = "Bilanoski";
people[1].fistName = "Stole";
people[1].lastName = "Lebata";
```


## Sorting algorithms

### Selection sort
Select number, then pick another, chech wich is smaller, if smaller, switch position then select another, do another check, if smaler switch if not move along.

**In pseudocode**
```text
For i from 0 to n-1
  Find smallest number between numbers[i] and numbers[n-1]
  Swap smallest number with numbers[i]
```

**Performace**
* O(n²) (worst case)
* Ω(n²) (best case)
* Θ(n²)


### Bubble sort
Similar as selection sort but goes two by two and switches smaller to the left. Keep repeating until there are switching, on the run which does not have switchig, it's sorted.

**In pseudocode**
```text
Repeat n-1 times
  For i from 0 to n-2
    If numbers[i] and numbers[i+1] are out of order
      Swap them
  If no swaps
    Quit
```

n-2 because we always compare with neighbour (i+1) so last one in loop should be one before last one in array. Otherwise I touch memory not associated with array.

**Performace**
* O(n²) (worst case)
* Ω(n) (best case, if data is already sorted)


## Recursion
Ability of a function to call itself.

**Check this out further**

### Merge sort
Sort left side and right side separately, for each side sorts from left to right two by two, add them to new array, repeat until sorted.

**In pseudocode**

```text
If only one number
  Quit
Else
  Sort left half of numbers
  Sort right half of numbewrs
  Merge sorted halves
```

**Performace**
* O(n log n) (worst case)
* Ω(n log n) (best case)
