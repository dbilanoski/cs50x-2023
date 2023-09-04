#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int is_key_valid(string k);

int main(int argc, string argv[])
{
    string k = argv[1];
    // Validation of the key argument
    if (argc != 2 || is_key_valid(k) == 0)

    {

        printf("Please provide a single argument as positive integer.\n");
        return 1;
    }

    // Take user input
    string plain = get_string("plaintext:  ");

    // Write switcheroo to change letter with k spaces
    // Convert key to number
    int kn = atoi(k);
    // Declare alphabet to use it later for switching letters
    const char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Placeholder for ciphertext
    // char cipher[strlen(plain)];
    // Did not use it at the end as it seems that printing the null terminated char is not a valid solution here

    // So print "ciphertext: " here, then do for loop for each char switheroo, then print \n at the end
    printf("ciphertext: ");

    // Spin each letter and perfom the switheroo
    for (int i = 0; i < strlen(plain); i++)
    {
        if (isalpha(plain[i]))
        {

            // Get current's letter index num in alphabet
            int z = 0;
            for (int j = 0; j < 26; j++)
            {
                if (tolower(alphabet[j]) == tolower(plain[i]))
                {
                    z = j;
                    break;
                }
            }

            // Calculate offset using key value and current index
            int n = (z + kn) % 26;
            // Get offsetted letter from alphabet and save it as string
            char c = (char)alphabet[n];

            if (isupper(plain[i]))
            {
                char cu = toupper(c);
                // strncat(cipher, &cu, 1);
                printf("%c", cu);
            }
            else
            {
                char cl = tolower(c);
                // strncat(cipher, &cl, 1);
                printf("%c", cl);
            }
        }
        else
        {

            char cp = plain[i];
            // strncat(cipher, &cp, 1);
            printf("%c", cp);
        }
    }

    // Output plaintext and ciphertext results
    // printf("ciphertext: %s\n", cipher);
    // So outputing a null terminated char as a result seems is not acceptible by this course validating system
    // Changing logic from appending letters to a variable to printing them directly from the loop

    printf("\n");
}

int is_key_valid(string k)
{
    for (int i = 0; i < strlen(k); i++)
    {
        if (isdigit(k[i]) == 0)
        {
            return 0;
        }
    }

    return 1;
}