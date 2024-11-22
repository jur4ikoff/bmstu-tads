#include "arr_queue.h"
#include "errors.h"
#include <stdio.h>

static void move_elements_to_begin(arr_queue_t *queue)
{
    int n = queue->end - queue->start;
    queue->end = queue->data + n;

    for (int i = 0; i < n; i++)
    {
        queue->data[i] = *queue->start;
        queue->start++;
    }
    queue->start = queue->data;
}

int arr_queue_create(arr_queue_t *queue)
{
    queue->size = MAX_QUEUE_SIZE;
    queue->start = queue->data;
    queue->end = queue->data;
    return ERR_OK;
}

void arr_queue_print_char(const arr_queue_t queue)
{
    // printf("%ld\n", sizeof(queue.data) / sizeof(queue.data[0]));
    if (queue.start - queue.end == 0)
    {
        printf("%sОчередь пустая%s\n", YELLOW, RESET);
        return;
    }
    data_t *start = queue.start;
    while (start != queue.end)
    {
        printf("%c ", start->element);
        start++;
    }
    printf("\n");
}

int arr_queue_push(arr_queue_t *queue, char element)
{
    if (queue->start > queue->end)
        return ERR_QUEUE_OVERFLOW;
    printf("%ld %d %ld\n", sizeof(data_t), (int)(queue->end - queue->start), queue->size * sizeof(data_t));
    if ((int)(queue->end - queue->start) >= (int)(queue->size * sizeof(data_t)))
        return ERR_QUEUE_OVERFLOW;

    queue->end->element = element;
    queue->end++;

    if (queue->end > queue->data + sizeof(queue->data) * queue->size)
        move_elements_to_begin(queue);
printf("%ld %d %ld\n\n", sizeof(data_t), (int)(queue->end - queue->start), queue->size * sizeof(data_t));
    return ERR_OK;
}

/*int arr_queue_pop(arr_queue_t *queue, char *element)
{
    if (queue->start > queue->end)
        return ERR_QUEUE_OVERFLOW;

    if ((size_t)(queue->end - queue->start) >= queue->size * sizeof(data_t))
        return ERR_QUEUE_OVERFLOW;
}*/
