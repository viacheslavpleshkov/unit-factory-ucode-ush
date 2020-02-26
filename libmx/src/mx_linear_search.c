#include "libmx.h"

int mx_linear_search(char **arr, const char *s) {
    int count = 0;
    while(arr && *arr != NULL) {
        if (!mx_strcmp(*arr, s))
            return count;
        arr++;
        count++;
    }
    return -1;
}
