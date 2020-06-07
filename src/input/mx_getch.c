#include "ush.h"

char *mx_add_history(t_input *input, int *flag, t_ush *ush, char *temp) {
    if (ush->history->data != NULL) {
        if (ush->history->next != NULL && *flag == 0) {
            *flag = 1;
            mx_strdel(&temp);
            temp = mx_strdup(ush->history->data);
        }
        mx_strdel(&ush->history->data);
    }
    ush->history->data = mx_strdup(input->command);
    return temp;
}

void mx_sort_history(t_ush *ush, char *temp) {
    char *p = mx_strdup(ush->history->data);

    mx_strdel(&ush->history->data);
    ush->history->data = mx_strdup(temp);
    while (ush->history->next != NULL)
        ush->history = ush->history->next;
    ush->history->data = p;
}

t_dbl_list *mx_addelem(t_dbl_list *history) {
    t_dbl_list *temp, *p;

    temp = (t_dbl_list *) malloc(sizeof (t_dbl_list));
    p = history->next; // сохранение указателя на следующий узел
    history->next = temp; // предыдущий узел указывает на создаваемый
    temp->next = p; // созданный узел указывает на следующий узел
    temp->prev = history; // созданный узел указывает на предыдущий узел
    temp->data = NULL;
    if (p != NULL)
        p->prev = temp;
    return temp;
}

void mx_free_step(t_input *input, char *temp) {
    mx_strdel(&temp);
    mx_strdel(&input->command);
    free(input);
}

int mx_getch(t_input *input) {
    int size = 0;

    size = read(0, &input->input_ch, 4);
    return size;
}
