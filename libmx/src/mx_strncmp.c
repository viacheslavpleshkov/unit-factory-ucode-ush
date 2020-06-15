#include "libmx.h"

int mx_strncmp(const char *s1, const char *s2, int n) {
    int i = 0;

    while (s1[i] && i < n) {
        if (s1[i] != s2[i]) 
            return s1[i] - s2[i];
        i++;
    }
    if (s2[i] && i < n)
        return s1[i] - s2[i];
    return 0;
}
