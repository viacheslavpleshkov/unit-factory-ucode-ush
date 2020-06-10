#include "ush.h"

void mx_com_sub(char **data, t_ush *ush) {
    t_com_sub *com_sub = mx_create_com_sub();
    int exit = 0;

    for (int i = 0; (*data)[i] != '\0'; i++) {
        if(mx_com_sub_space(data, com_sub, ush, i) == 1) {
            exit = 1;
            break;
        }
        if(mx_com_sub_back(data, com_sub, ush, i) == 1) {
            exit = 1;
            break;
        }
    }
    free(com_sub);
    if (exit == 1)
        mx_com_sub(data, ush);
}
