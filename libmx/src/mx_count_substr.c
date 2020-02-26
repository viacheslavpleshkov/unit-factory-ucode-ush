#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int counts = 0;
    char *temp = NULL;

    if (!str || !sub)
        return -1;
    temp = mx_strstr(str, sub);
    while (temp != NULL) { 
        temp++;
        temp = mx_strstr(temp, sub);
        counts++;
    }

    return counts;
}
