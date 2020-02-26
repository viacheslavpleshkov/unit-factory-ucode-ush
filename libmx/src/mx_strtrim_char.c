#include "libmx.h"

char *mx_strtrim_char(const char *str, char c) {
    int b = 0;
    int e = 0;

    if (!str)
        return NULL;
    e = mx_strlen(str) - 1;
    while(str[b] && str[b] == c) 
        b++;
    while (str[e] && str[e] == c)
        e--;
    if (e < b)
        return mx_strnew(0);
    return mx_strncpy(mx_strnew(e - b + 1), &str[b], e - b + 1);
}
