#include <cs50.h>
#include <stdio.h>


int main(void)
{
    // Promt user for input
    int rows = 0;
    do
    {
        rows = get_int("Height [1-8]: ");
    }
    while (rows < 1 || rows > 8);

    // Loop over rows to draw the each row
    for (int i = 1; i <= rows; i++)
    {
        int spaces = rows - i;
        int hashes = i;

        // Draw the spaces
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }

        // Draw the hashes
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }

        // Draw the hole
        printf("  ");

        // Draw the other side hashes
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }

        // New line for next row
        printf("\n");
    }
}