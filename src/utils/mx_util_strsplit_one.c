#include "ush.h"

static char *replace(const char *s, char *str_join) {
    int leng_s = mx_strlen(s);
    int leng_str_join = mx_strlen(str_join);
    char *name = NULL;
    int i = 0;
    int j = leng_str_join;
    name = mx_strnew(leng_s - leng_str_join);
    while (s[j]) {
        name[i] = s[j];
        i++;
        j++;
    }
    name[i] = '\0';
    return name;
}

static char **one_if(char *str_rep) {
    char **result = NULL;

    result = (char**) malloc(sizeof(char*) * (2));
    result[0] = mx_strdup(str_rep);
    result[1] = NULL;
    mx_strdel(&str_rep);
    return result;
}

static char **two_if(char *str_rep, char *temp_str, char *str_join, char *c) {
    char **result = NULL;
    int and = 0;
    int or = 0;

    result = (char**) malloc(sizeof(char*) * (3));
    temp_str = mx_strndup(str_rep, mx_get_substr_index(str_rep, c));
    result[0] = mx_strtrim(temp_str);
    and = mx_util_get_flag_index(str_rep, "&&");
    or = mx_util_get_flag_index(str_rep, "||");
    if ((and >= 0) && (and < or))
        str_join = mx_strjoin(result[0], "&&");
    else
        str_join = mx_strjoin(result[0], "||");
    result[1] = replace(str_rep, str_join);
    result[2] = NULL;
    mx_strdel(&str_join);
    mx_strdel(&temp_str);
    mx_strdel(&str_rep);
    return result;
}

char **mx_util_strsplit_one(const char *s, char *c) {
    char **result = NULL;
    char *str_join = NULL;
    char *str_rep = NULL;
    char *temp_str = NULL;

    str_rep  = mx_util_replace_operator((char *)s);
    if (mx_count_queue_operation(str_rep) == 0)
        result = one_if(str_rep);
    else
        result = two_if(str_rep, temp_str, str_join, c);
    return result;
}
