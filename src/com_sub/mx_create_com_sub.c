#include "ush.h"

t_com_sub* mx_create_com_sub() {
    t_com_sub *com_sub = (t_com_sub *)malloc(sizeof(t_com_sub));

    com_sub->back_first = 0;
    com_sub->back_first_index = 0;
    com_sub->back_end = 0;
    com_sub->back_end_index = 0;
    com_sub->space = 0;
    com_sub->space_first_index = 0;
    com_sub->space_end_index = 0;
    return com_sub;
}