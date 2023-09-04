#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Validation for provided key (len 26, only one argument)
    if (argc > 2 || argc < 2 || strlen(argv[1]) < 26)
    {
        printf("Please provide only one argument with 26 letters.\n");
        return 1;
    }

    // Validation for provided key (If letters or duplicates)
    string key = argv[1];

    for (int i = 0; i < 26; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Please provide a key with 26 letters.\n");
            return 1;
        }

        // To check for duplicates, another loop on same array with offset 1
        for (int k = i + 1; k < 26; k++)
        {
            if (tolower(key[i]) == tolower(key[k]))
            {
                printf("Please provide a key with 26 unique letters.\n");
                return 1;
            }
        }
    }

    // Get string from user (plaintext: )
    string text = get_string("plaintext: ");

    // Perform substitution based on the given key
    char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char ciphertext[100] = "";

    /*
      # PLAN
        * We need key and alphabet arrays (alphabet sorted) and one new array to put the result in
        * Loop over given text
        * For each character check if it's a letter
        * If letter:
          * Loop over alphabet, compare - if current text char matches current alphabet char, pull from key on same index to replace it
            * Before appending the key char to new array, check the text char case and preserve it
        * If not letter, just append it to the new array  
    */

    for (int i = 0; i < strlen(text); i++)
    {

        // If letter, do the swap otherwise just append what is originaly there
        if (isalpha(text[i]))
        {
            // Loop over alphabet
            // if current char matches current letter, pull same index from key to replace it
            for (int j = 0; j < 26; j++)
            {
                if (toupper(text[i]) == alphabet[j])
                {
                    // Check case, then append
                    if (islower(text[i]))
                    {
                        char s = tolower(key[j]);
                        strncat(ciphertext, &s, 1);
                    }
                    else
                    {
                        char s = toupper(key[j]);
                        strncat(ciphertext, &s, 1);
                    }
                    break;
                }
            }
        }
        else
        {
            strncat(ciphertext, &text[i], 1);
        }

    }

    // Output ciphertext: while preserving case of the letters
    printf("ciphertext: %s\n", ciphertext);

}