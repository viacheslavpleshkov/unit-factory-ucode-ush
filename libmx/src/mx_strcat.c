#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int len_s1 = mx_strlen(s1);
    int len_s2 = mx_strlen(s2);

    for (int i = len_s1; i < len_s1 + len_s2; i++) {
        s1[i] = *s2;
        s2++;
    }
    s1[len_s1 + len_s2] = '\0';
    return s1;    
}
