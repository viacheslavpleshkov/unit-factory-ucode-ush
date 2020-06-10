#include "ush.h"

static int get_flag_index(const char *str, const char *sub) {
    int len_str = 0;
    int len_sub = 0;

    if (!str || !sub)
        return -2;
    len_str = mx_strlen(str);
    len_sub = mx_strlen(sub);
    for (int i = 0; i <= len_str - len_sub; i++)
        if (!mx_strncmp(&str[i], sub, len_sub))
            return i;
    return INT_MAX;
}

static char *push_back_queue(char *logic, char *temp, t_queue **arr_queue) {
    char **arr_str = NULL;

    arr_str = mx_util_strsplit_one(temp, logic);
    mx_push_back_queue(arr_queue, arr_str[0], logic[0]);
    mx_strdel(&temp);
    temp = mx_strdup(arr_str[1]);
    mx_free_void_arr((void **)arr_str, mx_count_arr_el(arr_str));
    return temp;
}

void mx_insort_t_queue(char *arr, t_queue **arr_queue) {
    int count = mx_count_queue_operation(arr);
    int and = 0;
    int or = 0;
    char *temp = mx_strdup(arr);

    for (int j = 0; j <= count; j++) {
            and = get_flag_index(temp, "&&");
            or = get_flag_index(temp, "||");
            if ((and >= 0) && (and < or))
                temp = push_back_queue("&&", temp, arr_queue);
            else if ((or >= 0) && (or < and ))
                temp = push_back_queue("||", temp, arr_queue);
            else if (and == INT_MAX && or == INT_MAX) {
                if (temp == NULL)
                    temp = mx_strdup(arr);
                mx_push_back_queue(arr_queue, temp, '0');
            }
    }
    mx_strdel(&temp);
}
