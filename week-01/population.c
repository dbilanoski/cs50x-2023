#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int llamas_start = 0;
    int llamas_end = 0;

    // Get starting population from user
    do
    {
        llamas_start = get_int("Starting population size [> 9]: ");

    }
    while (llamas_start < 9);

    // Get ending population from user
    do
    {
        llamas_end = get_int("Ending population size [> than starting size]: ");

    }
    while (llamas_end < llamas_start);

    // Loop over each year to get the total count
    int population = llamas_start;
    int years = 0;

    while (population < llamas_end)
    {
        int births = population / 3;
        int deaths = population / 4;

        population = population + births - deaths;
        years ++;

    }

    printf("Years: %i\n", years);

}