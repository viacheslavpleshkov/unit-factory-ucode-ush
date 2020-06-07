#include "ush.h"

int mx_util_get_flag_index(const char *str, const char *sub) {
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
