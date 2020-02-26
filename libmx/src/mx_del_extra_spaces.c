#include "libmx.h"

static int check_len(const char *str) {
    int len = 0;

    for (int j = 0; str[j]; j++)
        if (!mx_isspace(str[j])) 
            len++;
    return len;
}

char *mx_del_extra_spaces(const char *str) {
    char *result = NULL;
    int k = 0;
    int len = 0;
    int i = 0;

    if (!str) return NULL;
    len = check_len(str) + mx_count_words_space(str) - 1;
    if (len < 0) 
        return mx_strnew(0);
    result = mx_strnew(len);
    while(str[i]) {
        while (mx_isspace(str[i]) && str[i]) 
            i++;
        for (; !mx_isspace(str[i]) && str[i]; i++, k++)
            result[k] = str[i];
        result[k] = ' ';
        k++;
    }
    return mx_strtrim(result);
}
