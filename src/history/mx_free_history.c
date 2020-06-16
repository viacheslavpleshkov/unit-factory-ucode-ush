#include "ush.h"

static t_dbl_list *deletelem(t_dbl_list *lst) {
    t_dbl_list *prev = lst->prev; // узел, предшествующий lst
    t_dbl_list *next = lst->next; // узел, следующий за lst
    if (prev != NULL)
        prev->next = lst->next; // переставляем указатель
    if (next != NULL)
        next->prev = lst->prev; // переставляем указатель
    mx_strdel(&lst->data);
    free(lst); // освобождаем память удаляемого элемента
    return(prev);
}

static void free_pids(t_pid *pids) {
    t_pid *temp = NULL;

    if (pids != NULL) {
        while (pids->prev != NULL) {
            temp = pids;
            pids = pids->prev;
            mx_strdel(&temp->str);
            free(temp);
        }
        mx_strdel(&pids->str);
        free(pids);
    }
}

void mx_free_ush(t_ush *ush) {
    if (ush != NULL) {
        while (ush->history->next != NULL)
            ush->history = ush->history->next;
        while (ush->history != NULL)
            ush->history = deletelem(ush->history);
        mx_strdel(&ush->ush_path);
        mx_strdel(&ush->pwd_l);
        free_pids(ush->pids);
        free(ush);
    }
}
