#include "libmx.h"

char *mx_strchr(const char *str, char c){
    int temp = mx_get_char_index(str, c);

    if (temp >= 0)
        return (char *)&str[temp];
    else
        return NULL;
}
