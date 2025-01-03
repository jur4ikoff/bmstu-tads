#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "constants.h"
#include "utils.h"
#include <time.h>

/*
// Получение длины целочисленного числа
int int_len(long long value)
{
    int count = 0;

    if (value == 0)
        return 1;

    while (value > 0)
    {
        count++;
        value /= 10;
    }

    return count;
}
*/

/**
 * @brief Функция для ввода строки
 */
int input_string(char *string, size_t max_len, char *message)
{
    printf("%s", message);
    if (!fgets(string, max_len, stdin))
        return ERR_INPUT_STRING;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_STRING_OVERFLOW;
    *newline = 0;

    if (strlen(string) < 1)
        return ERR_EMPTY_STRING;
    return ERR_OK;
}

/**
 * @brief Функция для вычисления вероятности
 */
bool random_chance(int percentage)
{
    if (percentage <= 0)
        return false;
    if (percentage >= 100)
        return true;

    int random_value = rand() % 100;
    return random_value < percentage;
}

/**
 * @brief Функция реализует ввод целого числа от пользователя
 */
int input_integer(int *number, char *message, int low_edge, int max_edge)
{
    printf("%s", message);
    if (scanf("%d", number) != 1)
        return ERR_INPUT_INTEGER_NUMBER;
    fgetc(stdin);

    if (*number < low_edge || *number > max_edge)
        return ERR_INPUT_INTEGER_NUMBER_RANGE;

    return ERR_OK;
}

/**
 * @brief Функция считывает из файла количество строк и количество столбцов
 */
int get_matrix_info(FILE *file, int *row, int *column)
{
    if (fscanf(file, "%d", row) != 1)
        return ERR_FILE_INPUT;

    if (fscanf(file, "%d", column) != 1)
        return ERR_FILE_INPUT;

    if (*row < 1 || *row > MAX_SIZE)
        return ERR_RANGE_MATRIX_SIZE;

    if (*column < 1 || *column > MAX_SIZE)
        return ERR_RANGE_MATRIX_SIZE;

    return ERR_OK;
}

void *max(void *value_1, void *value_2, size_t width)
{
    unsigned char buf1[MAX_WIDTH];
    unsigned char buf2[MAX_WIDTH];

    memcpy(buf1, value_1, width);
    memcpy(buf2, value_2, width);

    for (size_t i = 0; i < width; i++)
    {
        if (buf1[i] > buf2[i])
            return value_1;
        else
            return value_2;
    }
    return value_1;
}
