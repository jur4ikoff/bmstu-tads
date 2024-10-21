/*
Вариант 2

Задание общее
Разработать программу умножения или сложения разреженных матриц.
Предусмотреть возможность ввода данных, как с клавиатуры, так и использования
заранее подготовленных данных. Матрицы хранятся и выводятся в форме трех
объектов. Для небольших матриц можно дополнительно вывести матрицу в виде
матрицы. Величина матриц - любая (допустим, 1000*1000). Сравнить эффективность
(по памяти и по времени выполнения) стандартных алгоритмов обработки матриц с
алгоритмами обработки разреженных матриц при различной степени разреженности
матриц и различной размерности матриц.

Задание из варианта
Разреженная (содержащая много нулей) матрица хранится в форме 3-х объектов
(CSC):
- вектор A содержит значения ненулевых элементов;
- вектор IA содержит номера строк для элементов вектора A;
- вектор JA, в элементе Nk которого находится номер компонент в A и IA, с
которых начинается описание столбца Nk матрицы A.

1. Смоделировать операцию сложения двух матриц, хранящихся в этой
форме, с получением результата в той же форме.
2. Произвести операцию сложения, применяя стандартный алгоритм
работы с матрицами.
3. Сравнить время выполнения операций и объем памяти при
использовании этих 2-х алгоритмов при различном проценте заполнения
матриц.
*/

/* Чтобы заполнить матрицы самостоятельно, нужно запустить программу с флагом --manual (./app.exe --manual),
Для того, чтобы программа работала без лишнего вывода, запустить с флагом --quite*/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "errors.h"
#include "constants.h"
#include "utils.h"
#include "default_matrix.h"

typedef enum
{
    MENU_EXIT,
    MENU_FILL_MANUAL,
    MENU_FILL_RANDOM,
    MENU_PRINT_DEF,
    MENU_PRINT_CSC,
    MENU_ADD_DEF,
    MENU_ADD_CSC,
    MENU_COMPARE_EFFICIENCY,
    MENU_HELP
} menu_t;

void print_menu(void)
{
    printf("0 - Выход\n"
           "1 - Заполнить матрицы вручную\n"
           "2 - Заполнить матрицы рандомно\n"
           "2 - Вывести матрицы\n"
           "3 - Вывести матрицы в формате CSC\n"
           "4 - Сложить матрицы в обычном виде\n"
           "5 - Сложить матрицы в формате CSC\n"
           "6 - Сравнить эффективность\n"
           "7 - Справочная информация\n");
}

int input_operation(menu_t *operation)
{
    printf(">>Введите номер операции: ");
    int input, rc = ERR_OK;
    if ((rc = input_integer(&input, ">>Введите номер операции: ", 0, MAX_OPERATION)) != ERR_OK)
    {
        if (rc == ERR_INPUT_INTEGER_NUMBER_RANGE)
            rc = ERR_RANGE_OPERATION;
        return rc;
    }

    *operation = (menu_t)input;
    return rc;
}

void help(void)
{
    printf("Программа для сложения разреженных матриц в обычном виде, и в формате csc\n"
           "Для того чтобы заполнить две матрицы вручную, нужно ввести путь к двум файлам следующей структуры:\n"
           "На первой строке количество строк и столбцов\n"
           "На последующих строках находится целочисленная матрица\n\n");
}

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    print_menu();
    char filename_first[MAX_PATH_SIZE + 1], filename_second[MAX_PATH_SIZE + 1];
    matrix_t matrix_1 = {0}, matrix_2 = {0};
    FILE *file_1 = NULL, *file_2 = NULL;
    bool is_manual = false;
    if (argc == 2 && strcmp(argv[1], "--manual") == 0)
    {
        is_manual = true;
    }

    while (true)
    {
        menu_t operation;
        if ((rc = input_operation(&operation)) != ERR_OK)
        {
            print_error_message(rc);
            return rc;
        }

        if (operation == MENU_EXIT)
        {
            printf(">>Успешное завершение работы программы\n");
            break;
        }
        else if (operation == MENU_FILL_MANUAL)
        { // Заполнение матриц вручную
            // Ввод имени файла для первого файла
            if (is_manual)
            {
                if ((rc = input_string(filename_first, MAX_PATH_SIZE, ">>Введите путь к файлу с первой матрицей: ")) != ERR_OK)
                {
                    free_default_matrix(&matrix_1);
                    free_default_matrix(&matrix_2);
                    print_error_message(rc);
                    return rc;
                }
            }
            else
            {
                strcpy(filename_first, "matrix_1.txt");
            }

            file_1 = fopen(filename_first, "r");
            if (file_1 == NULL)
            {
                free_default_matrix(&matrix_1);
                free_default_matrix(&matrix_2);
                print_error_message(ERR_FILENAME);
                return ERR_FILENAME;
            }
            if ((rc = create_default_matrix(file_1, &matrix_1)) != ERR_OK)
            {
                free_default_matrix(&matrix_1);
                free_default_matrix(&matrix_2);
                fclose(file_1);
                print_error_message(rc);
                return rc;
            }

            if ((rc = fill_matrix_from_file(file_1, &matrix_1)) != ERR_OK)
            {
                free_default_matrix(&matrix_1);
                free_default_matrix(&matrix_2);
                fclose(file_1);
                print_error_message(rc);
                return rc;
            }
            fclose(file_1);
            printf(">>Матрица из файла %s\n успешно прочитана\n", filename_first);

            // Ввод имени файла для второго файла
            if (is_manual)
            {
                if ((rc = input_string(filename_second, MAX_PATH_SIZE, ">>Введите путь к файлу со второй матрицей: ")) != ERR_OK)
                {
                    free_default_matrix(&matrix_1);
                    free_default_matrix(&matrix_2);
                    print_error_message(rc);
                    return rc;
                }
            }
            else
                strcpy(filename_second, "matrix_2.txt");

            file_2 = fopen(filename_second, "r");
            if (file_2 == NULL)
            {
                free_default_matrix(&matrix_1);
                free_default_matrix(&matrix_2);
                print_error_message(ERR_FILENAME);
                return ERR_FILENAME;
            }

            if ((rc = create_default_matrix(file_2, &matrix_2)) != ERR_OK)
            {
                free_default_matrix(&matrix_1);
                free_default_matrix(&matrix_2);
                fclose(file_2);
                print_error_message(rc);
                return rc;
            }

            if ((rc = fill_matrix_from_file(file_2, &matrix_2)) != ERR_OK)
            {
                free_default_matrix(&matrix_1);
                free_default_matrix(&matrix_2);
                fclose(file_2);
                print_error_message(rc);
                return rc;
            }

            fclose(file_2);
            printf(">>Матрица из файла %s\n успешно прочитана\n", filename_second);
        }
        else if (operation == MENU_FILL_RANDOM)
        {
            // Заполнение матрицы рандомно
            int n, m, percentiage;
            if ((rc = input_integer(&n, "Введите количество строк в первой матрице: ", 0, MAX_SIZE)) != ERR_OK)
            {
                free_default_matrix(&matrix_1);
                free_default_matrix(&matrix_2);
                print_error_message(rc);
                return rc;
            }

            if ((rc = input_integer(&m, "Введите количество столбцов в первой матрице: ", 0, MAX_SIZE)) != ERR_OK)
            {
                free_default_matrix(&matrix_1);
                free_default_matrix(&matrix_2);
                print_error_message(rc);
                return rc;
            }

            if ((rc = input_integer(&percentiage, "Введите процент заполнения первой матрицы: ", 0, 100)) != ERR_OK)
            {
                free_default_matrix(&matrix_1);
                free_default_matrix(&matrix_2);
                print_error_message(rc);
                return rc;
            }

        }
        else if (operation == MENU_PRINT_DEF)
        {
            // Вывод матрицы в обычном виде
            ;
        }
        else if (operation == MENU_PRINT_CSC)
        {
            // Вывод матрицы в формате CSC
            ;
        }
        else if (operation == MENU_ADD_DEF)
        {
            // Сложение матриц в обычном виде
            ;
        }
        else if (operation == MENU_ADD_CSC)
        {
            // Сложение матриц в формате CSC
            ;
        }
        else if (operation == MENU_COMPARE_EFFICIENCY)
        {
            // Сравнение эффект
            ;
        }
        else if (operation == MENU_HELP)
        {
            // Справочная информация
            help();
        }
    }

    free_default_matrix(&matrix_1);
    free_default_matrix(&matrix_2);
    return rc;
}