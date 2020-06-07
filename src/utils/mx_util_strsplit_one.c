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

char **mx_util_strsplit_one(const char *s, char *c) {
    char **result = NULL;
    char *str_join = NULL;
    char *str_replace = NULL;
    char *temp_str = NULL;
    int and = 0;
    int or = 0;

    str_replace  = mx_util_replace_operator((char *)s);
    if(mx_count_queue_operation(str_replace) == 0){
        result = (char**) malloc(sizeof(char*) * (2));
        result[0] = mx_strdup(str_replace);
        result[1] = NULL;

    }
    else {
        result = (char**) malloc(sizeof(char*) * (3));
        temp_str = mx_strndup(str_replace, mx_get_substr_index(str_replace, c));
        result[0] = mx_strtrim(temp_str);
        and = mx_util_get_flag_index(str_replace, "&&");
        or = mx_util_get_flag_index(str_replace, "||");
        if ((and >= 0) && (and < or))
            str_join = mx_strjoin(result[0], "&&");
        else
            str_join = mx_strjoin(result[0], "||");
        result[1] = replace(str_replace, str_join);
        result[2] = NULL;
    }
    mx_strdel(&str_join);
    mx_strdel(&temp_str);
    mx_strdel(&str_replace);
    return result;

}
