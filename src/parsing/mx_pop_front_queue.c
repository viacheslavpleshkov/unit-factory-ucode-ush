#include "ush.h"

void mx_pop_front_queue(t_queue **head) {
    t_queue *temp = NULL;

    if (head == NULL || *head == NULL)
        return;
    if ((*head)->next == NULL) {
        free((*head)->data);
        free(*head);
        *head = NULL;
    }
    else {
        temp = (*head)->next;
        free((*head)->data);
        free(*head);
        *head = temp;
    }
}
