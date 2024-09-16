#include "input_number.h"

void swap(char *string, size_t index1, size_t index2)
{
    char buffer = string[index1];
    string[index1] = string[index2];
    string[index2] = buffer;
}

int count_symbols(char *string, char c)
{
    int count = 0;
    char *ptr = string;
    while (*ptr != 0)
    {
        if (*ptr == c)
            count++;

        ptr++;
    }

    return count;
}

int is_symbol(char c)
{
    // Проверяем, является ли символ буквой
    if (isalpha(c))
        return 1; // Это буква

    // Проверяем, является ли символ знаком операции
    switch (c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
    case '<':
    case '>':
    case '&':
    case '|':
    case '^':
    case '!':
        return 1; // Это оператор
    default:
        return 0; // Ни буква, ни оператор
    }
}

int find_exp(number_t *number, char *string)
{
    size_t len = strlen(string);
    for (size_t i = 0; i < len; i++)
    {
        if (is_symbol(string[i]) != 0)
        {
            if (string[i] == 'e' || string[i] == 'E')
            {
                char *ptr = string + i + 1;
                if (*ptr == 0)
                    return ERR_ORDER_CHAR;

                errno = 0;
                char *endptr;
                int value = (int)strtol(ptr, &endptr, 10);

                if (errno == ERANGE || *endptr != '\0')
                    return ERR_INPUT_CHAR;

                if (abs((int)value) > MAX_ORDER)
                    return ERR_ORDER_SIZE;
                number->order = value;

                ptr = string + i;
                *ptr = '\0';

                return ERR_OK;
            }
            else
                return ERR_INPUT_CHAR;
        }
    }

    return ERR_OK;
}

int process_number(number_t *number, char *string)
{
    size_t len = strlen(string);
    for (size_t i = 0; i < len; i++)
    {
        if (number->mantise_size > MAX_MANTISE)
            return ERR_MANTISE_SIZE;

        if (number->order > MAX_ORDER)
            return ERR_ORDER_SIZE;

        if (string[i] != '.')
        {
            number->mantise[number->mantise_size] = string[i] - '0';
            number->mantise_size++;
            number->order++;
        }
        else
        {
            char *ptr = string + i + 1;
            while (*ptr != 0)
            {
                number->mantise[number->mantise_size] = *ptr - '0';
                number->mantise_size++;
                ptr++;
            }
            return ERR_OK;
        }
    }
    return ERR_OK;
}