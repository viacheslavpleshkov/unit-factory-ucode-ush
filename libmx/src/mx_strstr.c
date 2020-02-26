#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    int len_s1 = mx_strlen(haystack);
    int len_s2 = mx_strlen(needle);

    if (!len_s2)
        return (char*) haystack;
    for (int i = 0; i <= len_s1 - len_s2; i++) 
        if (!mx_strncmp(&haystack[i], needle, len_s2))
            return (char*) &haystack[i];   
    return NULL;
}
