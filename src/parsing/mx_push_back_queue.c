#include "ush.h"

void mx_push_back_queue(t_queue **queue, char *data, char operation) {
    t_queue *back_list = mx_create_queue(data, operation);
    t_queue *temp = NULL;

    if (*queue == NULL)
        *queue = back_list;
    else {
        temp = *queue;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = back_list;
    }
}
