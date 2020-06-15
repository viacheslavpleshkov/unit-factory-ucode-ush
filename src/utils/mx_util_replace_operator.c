#include "ush.h"

char *mx_util_replace_operator(char *s) {
    char *temp = mx_strtrim(s);
    char *temp_two = NULL;

    if (mx_get_substr_index(temp," && ")  >= 0)
        temp_two = mx_replace_substr(temp, " && ", "&&");
    else if (mx_get_substr_index(temp," || ")  >= 0)
        temp_two = mx_replace_substr(temp, " || ", "||");
    else
        temp_two = mx_strdup(temp);
    mx_strdel(&temp);
    return temp_two;
}

