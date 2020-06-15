#include "ush.h"

static void case_or(t_queue **queue, int i) {
    mx_pop_front_queue(&queue[i]);
    while (queue[i] != NULL && queue[i]->operator == '|')
        mx_pop_front_queue(&queue[i]);
    if (queue[i] != NULL)
        mx_pop_front_queue(&queue[i]);
}

static void case_and_status_1(t_queue **queue, int i) {
    mx_pop_front_queue(&queue[i]);
    while (queue[i] != NULL && (queue[i]->operator == '&'
            || queue[i]->operator == '0')) {
        mx_pop_front_queue(&queue[i]);
    }
}
int mx_push_execute_queue(t_queue **queue, t_ush *ush) {
    int status = 0;

    for (int i = 0; queue[i] != NULL; i++) {
        while (queue[i] != NULL) {
            mx_com_sub(&queue[i]->data, ush);
            status = mx_execute(ush, queue[i]->data, 0, NULL);
            if (ush->exit_status != -1) {
                mx_pop_front_queue(&queue[i]);
                return status;
            }
            if (status == 0 && queue[i]->operator == '&') {
                mx_pop_front_queue(&queue[i]);
                continue;
            }
            else if (status == 1 && queue[i]->operator == '&') {
                case_and_status_1(queue, i);
                continue;
            }
            else if (queue[i]->operator == '|' && status == 0) {
                case_or(queue, i);
                continue;
            }
            else
                mx_pop_front_queue(&queue[i]);
        }
    }
    return status;
}
