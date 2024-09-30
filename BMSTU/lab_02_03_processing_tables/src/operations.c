#include "operations.h"
#include "errors.h"
#include "stdio.h"
#include "constants.h"

// Меню программы
void print_menu(void)
{
    printf(">Возможности программы\n"
           " 0 - Выход\n"
           " 1 - Добавить запись в конец таблицы\n 2 - Удалить запись по ключу\n"
           " 3 - Просмотр отсортированной таблицы ключей\n 4 - Вывод упорядоченной исходной таблицы\n"
           " 5 - Вывод исходной таблицы в упорядоченном виде, используя упорядоченную таблицу ключей\n"
           " 6 - Вывод результатов использования различных алгоритмов сортировок\n"
           " 7 - Вывод результатов сравнения эффективности работы программы\n"
           " 8 - Выбрать базу данных (таблицу)\n"
           " 9 - Вывести иформацию о программе\n");
}

int input_operation(operations_t *operation)
{
    int operation_number;
    printf(">Выберите действие: ");
    if (scanf("%d", &operation_number) != 1)
        return ERR_OPERATION_INPUT;
    fgetc(stdin);

    if (operation_number < 0 || operation_number > OPERATIONS_COUNT)
        return ERR_OPERATION_COUNT;

    *operation = (operations_t)operation_number;
    return ERR_OK;
}
