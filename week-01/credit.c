#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int luhn_reversals(long number);
int digit_count(long number);

int main(void)
{
    // Ask user for input
    long card_num = get_long("Enter card number: ");

    // Get result against Luhn algorithm
    long luhn_result = luhn_reversals(card_num);

    // Count digits
    int digits = digit_count(card_num);

    // Validate the card
    if (luhn_result % 10 != 0 || card_num < 0 || digits < 13)
    {
        printf("INVALID\n");
        return 0;
    }

    // Get first 2 digits
    long first_two_digits = card_num;
    while (first_two_digits >= 100)
    {
        first_two_digits = first_two_digits / 10;
    }

    // Check card vendor
    if (first_two_digits == 34 || first_two_digits == 37)
    {
        printf("AMEX\n");
    }
    else if (first_two_digits > 50 && first_two_digits < 56)
    {
        printf("MASTERCARD\n");
    }
    else if (first_two_digits / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;

}


int luhn_reversals(long number)
{
    long n = number;
    long evens_sum = 0;
    char product_digits[20];
    long product_digits_num = 0;
    long product_digits_sum = 0;
    int count = 1;

    // FIRST PART
    // Get reversed odds and multiply each by 2, then sum product digits
    while (n > 0)
    {
        // Get each second in reversed number
        if (count % 2 == 0)
        {
            // Convert digit to string so I have product digits which I can append to variable
            char digit_to_string[10];
            sprintf(digit_to_string, "%ld", (n % 10) * 2);

            // Append converted digit to product_digits variable
            strcat(product_digits, digit_to_string);
        }
        n /= 10;
        count++;
    }
    // Now we have all digits appended, convert them back to numbers
    product_digits_num = strtol(product_digits, NULL, 10);

    // Sum the digits
    while (product_digits_num > 0)
    {
        product_digits_sum += product_digits_num % 10;
        product_digits_num /= 10;
    }

    // SECOND PART
    // Get reversed evens and sum them
    n = number; // Reset n back to input number
    while (n > 0)
    {
        evens_sum += (n % 10);
        n /= 100;
    }

    int result = product_digits_sum + evens_sum;
    return result;
}

int digit_count(long number)
{
    long n = number;
    int result = 0;
    while (n != 0)
    {
        n /= 10;
        result++;
    }
    return result;
}