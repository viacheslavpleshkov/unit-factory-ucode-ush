#include "libmx.h"

void mx_pop_index(t_list **list, int index) {
    t_list *last = *list;
    t_list *present = last -> next;

    if (index <= 0) {
        mx_pop_front(list);
        return;
    }
    if (index >= mx_list_size(*list)) {
        mx_pop_back(list);
        return;
    }

    for (int i = 1; i < index; i++) {
        present = present -> next;
        last = last -> next;
    }
    last -> next = present -> next;
    free(present);
}
