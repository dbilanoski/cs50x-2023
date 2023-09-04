#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<math.h>

int get_coleman_liau_result(float l, float s);
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{

    // Get text from user
    string text = get_string("Text: ");

    // Count sentences, words and letters
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Get average number of letters per 100 words
    float letters_in_100w = ((float)(letters)) / words * 100;

    // Get averate number of sentences per 100 words
    float sentences_in_100w = ((float)(sentences)) / words * 100;

    // Get Coleman-Liau score index
    int grade = get_coleman_liau_result(letters_in_100w, sentences_in_100w);
    printf("%i\n", grade);

    // Output result Grade x
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}


int get_coleman_liau_result(float l, float s)
{
    float result = 0.0588 * l - 0.296 * s - 15.8;
    int r = round(result);
    return r;
}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (tolower(text[i]) >= 'a' && tolower(text[i]) <= 'z')
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        // typecasting
        int l = (int)(text[i]);
        // If char is 32 (asci for space) and one before character was not 32 (so we can have multiple spaces)
        if (l == 32 && ((int)(text[i - 1]) != 32))
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        // typecasting
        int l = (int)(text[i]);
        // If char is !, . or ?
        if (l == 33 || l == 46 || l == 63)
        {
            count++;
        }
    }
    return count;
}