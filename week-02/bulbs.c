#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void convert_to_binary(int (*arr)[8], string text, int len);

int main(void)
{
    // Get user input in letters
    string text = get_string("Text: ");
    // Calculate lenght of the text
    int text_lenght = strlen(text);

    // Convert numbers to bits (8-bit system)
    // C function apparently cannot return an array, so placeholder here
    int number_binary[text_lenght][8];
    convert_to_binary(number_binary, text, text_lenght);

    // Print the bulbs
    for (int i = 0; i < text_lenght; i++)
    {
        for (int a = 0; a < 8; a++)
        {
            print_bulb(number_binary[i][a]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

void convert_to_binary(int (*arr)[8], string text, int len)
{
    // Get text > loop over each letter > convert to decimal > convert it to binary > loop over it and append it to arr[][]
    for (int i = 0; i < len; i++)
    {
        // Current letter to decimal number
        int current_num = (int)(text[i]);
        // Lenght of the current bit
        int current_num_len = 0;
        // Current byte
        int current_byte[BITS_IN_BYTE] = {0, 0, 0, 0, 0, 0, 0, 0};

        // Create current byte (will be reversed so will need it backwards)
        while (current_num > 0)
        {
            current_byte[current_num_len] = current_num % 2;
            current_num /= 2;
            current_num_len++;
        }

        // Reverse it and append to arr[][]
        for (int x = 0; x < BITS_IN_BYTE; x++)
        {
            arr[i][BITS_IN_BYTE - 1 - x] = current_byte[x];
        }
    }
}