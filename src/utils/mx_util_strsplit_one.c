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

static char **two_if(char *str_rep, char *c) {
    char **result = (char**) malloc(sizeof(char*) * (3));
    int leng = mx_get_substr_index(str_rep, c);
    char *temp_str = mx_strndup(str_rep, leng);
    char *str_replace = mx_strndup(str_rep, leng + 2);
    char *str_trim = NULL;

    result[0] = temp_str;
    str_trim = replace(str_rep, str_replace);
    result[1] = mx_strtrim(str_trim);
    result[2] = NULL;
    mx_strdel(&str_replace);
    mx_strdel(&str_trim);
    return result;
}

char **mx_util_strsplit_one(const char *s, char *c) {
    char **result = NULL;
    char *str_rep = NULL;
    str_rep = mx_util_replace_operator((char *)s);
    if (mx_count_queue_operation(str_rep) == 0)
        result = one_if(str_rep);
    else
        result = two_if(str_rep, c);
    mx_strdel(&str_rep);
    return result;
}

