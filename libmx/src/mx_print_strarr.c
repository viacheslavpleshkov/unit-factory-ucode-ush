#include "libmx.h"

void mx_print_strarr(char **arr, const char *delim) {
    int i = 0;

    if (!delim || !arr)
        return;
    while(arr[i]) {
        if (i != 0)
            mx_printstr(delim);
        mx_printstr(arr[i]);
        i++;
    }
    if (i > 0)
        mx_printstr("\n");
}
