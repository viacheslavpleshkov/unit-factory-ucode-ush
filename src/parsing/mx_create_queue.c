#include "ush.h"

t_queue *mx_create_queue(char *data, char operation) {
    t_queue *new_node = NULL;

    if (!data)
        return NULL;
    else {
        new_node = (t_queue *)malloc(sizeof(t_queue));
        if (!new_node)
            return NULL;
        new_node->data = mx_strdup(data);
        new_node->operator = operation;
        new_node->next = NULL;
        return new_node;
    }
}
