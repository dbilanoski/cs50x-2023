#include <stdio.h>
#include<cs50.h>

int main(void)
{
    // Prompt user for input
    string userInput = get_string("What's your name? ");
    // Print out the message
    printf("Hello, %s\n", userInput);
}