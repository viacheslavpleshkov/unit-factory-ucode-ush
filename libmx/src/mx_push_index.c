#include "libmx.h"

void mx_push_index(t_list **list, void *data, int index) {
    t_list *new = NULL;
    t_list *last = *list;
    t_list *present = NULL;

    if (index <= 0) {
        mx_push_front(list, data);
        return;
    }
    if (index >= mx_list_size(*list)) {
        mx_push_back(list, data);
        return;
    } 
    new = mx_create_node(data);
    present = last -> next;
    for (int i = 1; i < index; i++) {
        present = present -> next;
        last = last -> next;
    }
    last -> next = new;
    new -> next = present;
}
