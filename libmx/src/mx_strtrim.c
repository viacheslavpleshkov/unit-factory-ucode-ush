#include "libmx.h"

char *mx_strtrim(const char *str) {
    int b = 0;
    int e = 0;

    if (!str)
        return NULL;

    e = mx_strlen(str) - 1;

    while(str[b] && mx_isspace(str[b])) 
        b++;

    while (str[e] && mx_isspace(str[e]))
        e--;

    if (e < b)
        return mx_strnew(0);

    return mx_strncpy(mx_strnew(e - b + 1), &str[b], e - b + 1);
}
