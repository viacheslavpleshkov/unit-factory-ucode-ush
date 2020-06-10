#include "ush.h"

void static find_com_sub(t_com_sub *com_sub, char **data, int i) {
    if ((*data)[i] == '$' && (*data)[i + 1] == '(') {
        if (com_sub->back_first == 0) {
            com_sub->back_first++;
            com_sub->back_first_index = i;
        }
    }
    if (com_sub->back_first == 1 && (*data)[i] == ')') {
        com_sub->back_end++;
        com_sub->back_end_index = i;
    }
}

static void insert_com_sub(t_com_sub *c, char **data, t_ush *ush) {
    c->temp_str = mx_util_strindup(*data,
            c->back_first_index + 2, c->back_end_index);
    c->status = mx_execute(ush, c->temp_str, 1, &c->cout_execute);
    c->temp_join = mx_strjoin("$(", c->temp_str);
    mx_strdel(&c->temp_str);
    c->temp_str = mx_strjoin(c->temp_join, ")");
}

int mx_com_sub_back(char **data, t_com_sub *c, t_ush *ush, int i) {
    find_com_sub(c, data, i);
    if (c->back_first_index < c->back_end_index) {
        insert_com_sub(c, data, ush);
        if (c->status == 0 && strlen(c->cout_execute) > 0)
            c->temp_data = mx_replace_substr(*data,
                    c->temp_str, c->cout_execute);
        else if (strlen(c->cout_execute) > 0)
            c->temp_data = mx_replace_substr(*data, c->temp_str, "");
        mx_com_sub_free(c);
        if (c->temp_data != NULL) {
            mx_strdel(data);
            *data = c->temp_data;
            return 1;
        }
    }
    return 0;
}
