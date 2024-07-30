#include <cs50.h>
#include <math.h>
#include <stdio.h>

long int ten_to_the(int n);
int get_first_n_digits(long int cc_number, int nb_digits, int n); // where n is the number of digits to extract
bool validate_checksum(long int cc_number, int nb_digits);

int main(void)
{
    long int cc_number = 0;
    int nb_digits = 0;
    bool is_valid_checksum = false;
    int valid_prefix_AMEX[] = {34, 37};
    int valid_prefix_MASTERCARD[] = {51, 52, 53, 54,55};
    int valid_prefix_VISA[] = {4};
    int valid_nb_digits_AMEX = 15;
    int valid_nb_digits_MASTERCARD_OR_VISA = 16;
    int valid_nb_digits_VISA_ONLY = 13;

    cc_number = get_long("Number: ");
    nb_digits = (int) floor(log10(cc_number)) + 1; //calculate number of digits in the user provided input

    is_valid_checksum = validate_checksum(cc_number, nb_digits);

    // Check for AMEX and exit on success

    if (is_valid_checksum)
    {
        if (nb_digits == valid_nb_digits_AMEX) // check for AMEX
        {
            int first_two_digits = get_first_n_digits(cc_number, nb_digits, 2);
            for (int i = 0; i < sizeof(valid_prefix_AMEX) / sizeof(valid_prefix_AMEX[0]); i++)
            {
                if (first_two_digits == valid_prefix_AMEX[i])
                {
                    printf("AMEX\n");
                    return 0;
                }
            }
        }
        if (nb_digits == valid_nb_digits_MASTERCARD_OR_VISA) // Check for MASTERCARD or VISA with 16 digits
        {
            int first_two_digits = get_first_n_digits(cc_number, nb_digits, 2);
            for (int i = 0; i < sizeof(valid_prefix_MASTERCARD) / sizeof(valid_prefix_MASTERCARD[0]); i++)
            {
                if (first_two_digits == valid_prefix_MASTERCARD[i])
                {
                    printf("MASTERCARD\n");
                    return 0;
                }
            }
            int first_digit = get_first_n_digits(cc_number, nb_digits, 1);
            for (int i = 0; i < sizeof(valid_prefix_VISA) / sizeof(valid_prefix_VISA[0]); i++)
            {
                if (first_digit == valid_prefix_VISA[i])
                {
                    printf("VISA\n");
                    return 0;
                }
            }
        }
        if (nb_digits == valid_nb_digits_VISA_ONLY) // Check for VISA with 13 digits
        {
            int first_digit = get_first_n_digits(cc_number, nb_digits, 1);
            for (int i = 0; i < sizeof(valid_prefix_VISA) / sizeof(valid_prefix_VISA[0]); i++)
            {
                if (first_digit == valid_prefix_VISA[i])
                {
                    printf("VISA\n");
                    return 0;
                }
            }
        }

    }

    // If no previous check validated, return INVALID and exit
    printf("INVALID\n");
}

int get_first_n_digits(long int cc_number, int nb_digits, int n)
{

    return ((cc_number / ten_to_the(nb_digits - n)) % ten_to_the(n));
}

bool validate_checksum(long int cc_number, int nb_digits)
{
    int temp_digit_times_two = 0;
    int temp_sum_digit_times_two = 0;
    int temp_sum_digit_not_times_two = 0;
    int last_operation_multiplied_by_two = true;
    for (int i = 0; i < nb_digits; i++) // goes through the cc_number long int digit by digit to perform computation required by Luhn’s Algorithm
    {
        if (last_operation_multiplied_by_two)
        {
            temp_sum_digit_not_times_two += (cc_number / ten_to_the(i)) % 10;
            last_operation_multiplied_by_two = false;
        }
        else
        {
            temp_digit_times_two = ((cc_number / ten_to_the(i)) % 10) * 2;
            if (temp_digit_times_two >= 10)
            {
                temp_sum_digit_times_two +=
                    (temp_digit_times_two % 10 + (temp_digit_times_two / 10) % 10);
            }
            else
            {
                temp_sum_digit_times_two += temp_digit_times_two;
            }
            last_operation_multiplied_by_two = true;
        }
    }

    if ((temp_sum_digit_not_times_two + temp_sum_digit_times_two) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

long int ten_to_the(int n) // helper function for moving through the long int digit by digit
{
    long int result = 1;
    for (int i = 0; i < n; i++)
    {
        result *= 10;
    }
    return result;
}
