# Data structures
 
## Stacks and Queues

Queues - line, ordered as FIFO (first in first out) (example queue in store)
Has two functions - enqueue (add to the end of the que) and dequeue (remove from the begining of the queue)

Stacks - same "line" concept, ordered as LIFO (last in first out) (example stack of plates)
Has two functions - push (add to the top of the stack) and pop (remove from the top of the stack)

Example for stack
```c
typedef struct
{
  person people[CAPACITY]; // total possible size for stack
  int size; // current size of the stack
}

// Downsize of this is that's finite (precise size is always finite)
 
```

## Resizing arrays

So how to resize staticly declared array?

One way is to copy is to another, bigger array, then deleting the old.
By using malloc, we are requesting new chunk of memory, then copying current to new, then freeing the old one.
But this is also inefficient, as it requires constant copying.

```c
int main(void)
{
  // let's say I need three sized array of integers
  int *list = malloc(3 * sizeof(int));

  // to which I assign some values
  list[0] = 1;
  list[1] = 2;
  list[2] = 3;

  // So later on I suddenly need the forth value to be added
  // by this example I'll ask for a four sized chunk of memory

  int *temp = malloc(4 * sizeof(int));

  // then copy values from old to new with a for loop
  for (int i = 0; i < 3; i ++)
  {
    temp[i] = list[i];
  }
  // then add forth valu
  tmp[3] = 4;

  // then I free the old chund allocated to "list" variable and point list variable to new chunk of memory allocated to "temp" variable
  free(list);
  list = temp;
}

```
Better approach in last example would be, instead to ask completely new chunk of memory with malloc, to use realloc().
It won't be more efficient, but less code and manual work.

### realoc(what-to-expand, by-how-many)

Funciton used for reallocating mememory.

On previous example:

```c
int main(void)
{
  // let's say I need three sized array of integers
  int *list = malloc(3 * sizeof(int));

  // to which I assign some values
  list[0] = 1;
  list[1] = 2;
  list[2] = 3;

  // So later on I suddenly need the forth value to be added
  // by this example I'll ask for a four sized chunk of memory

  int *temp = realloc(list, 4 * sizeof(int));

  // no need to copy values manually, realloc handles that as well. Good idea in generall is to check if allocation(malloc) or reallocation(realloc) went well by checking the function's return value. If null, not good, exit immidiately

  // I could skip using new variable temp here, but having it this way is checking the return value if the reallocation request was succesfully
  if (temp == NULL)
  {
    // not good, let's free old chunk and get the hell out of here
    free(list);
    return 1;
  }

  // now I point list variable to the reallocated memory
  list = temp;

  // then I add fourth vlaue
  tmp[3] = 4;
}
```

## Linked lists
Stiching data stuctures using references to addresses in memory which are not needed to be next to each other.

Here we are dealing with nodes - each node has a current value, and a metadata value which is a pointer to the address in memory of the next value, thus we are creating a linked lists. It all starts with a block referencing memory address of the first node.

```c
typedef struct
{
  // Current value
  int number;
  // Pointer to the next node structure
    // Needs to have struct keyword
    // next is just a variable name as a placeholder
  struct node *next;
}
node;
```

### Downsides (in relation to arrays)
* Uses more memory
* We cannot index into it as current node only knows about next one
* We cannot use binary search as bytes are not consequtive

### Example (building a stack)

```c
// Here we create prototype datastructure for the linked list
typedef struct bide
{
  int number;
  struct node *next;
}
node;

int main(void)
{
  
  // Say I want to make list of 4 items
  int list_size = 4;
  
  // First we declare vaiable which will be a reference to our list
  node *list = NULL; // at this point, this is linked list of zero items

  // For each of list item, create and configure a node
  for (int = i; i < list_size; i++)
  {
    // We allocate chunk of memory for the first(or next but still gonna be first as we are prepending here) list item we want to create
    node *n = malloc(sizeof(node));
    
    // Error cheching with memory allocation
    if (n == NULL)
    {
    // not good, exit immidiately
    return 1;
    }

    // Then we set the value for the current item
    n->number = i; //same as (*n).number = i, dot notation

    // Then we clear the garbage values from the next item (here we are assuming this is the last item in the list, otherwise n.next would be pointer to the next item
    n->next = NULL

    // Then we point the current.next to the begining of the list as we are prepending numbers here
    n->next = list;

    // Then we update the list to point to this node (since we are prepending, this is now new first item)
    list = n;
  }

// How to loop over linked list? While loop while temporary pointer returns NULL

// Our counter variable, will iterate it until it returns NULL
node *ptr = list; 
while (ptr != NULL) //while current pointer is valid chunk of memory

  // Print each value
  printf("%i\n"m ptr->number); // same as (*ptr).number, dot notation, I want to go to the ptr memory address and get value under "number"
  // Update ptr so it has the pointer to the next list item (current (*ptr).next value)
  ptr = ptr->next;
}

// Version with Foor loop
for (node *ptr = list; ptr != NULL; ptr = ptr->next)
{
  // Same code as in while loop here
  // Less code to write but looks more cryptic
}


// Free memory at the end
// Again I loop over list, but since I'm clearing memory, I will not be able to set ptr on each iteration as I am freeing it
// So temporary variable to copy it's value while clearing it

ptr = list
while (ptr != NULL)
{
  // Temp variable to store the memory address of the next node
  node *next = ptr->next;
  // Free current node
  free(ptr);
  // Update ptr to the next node from the temp variable
  ptr = next;
}

```

## Trees
Nodes connected in a downside tree like structure top to bottom.
This way we get two dimensional approach where we combine array and linked list logic.

Basic example

```c
typedef struct node
{
  int number;
  struct node left;
  struct node right;
}

```
Binary seach tree needs to be sorted top to bottom, smaller values left, biger to the right.

## Dictionaries
Key-value pairs.

## Hash tables
Grouping values by common quality reducing the size of the problem. Example is grouping names which are holding numbers(values) by letter.  

It's an array of linked lists.

## Tries
A try is a tree where each node is an array. So array of arrays of arrays of arrays until you get final letter of name.
So execution time is by how many letter name has, so on input key, not on the problem size.

Example
```c
type struct node
{
  char *number;
  struct node *children[26];
}

```
