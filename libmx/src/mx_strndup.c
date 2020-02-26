#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    size_t len = 0;

    if (!s1)
    	return NULL;
    len = mx_strlen(s1);
    if (len < n)
        return mx_strncpy(mx_strnew(len), s1, len);
    else
        return mx_strncpy(mx_strnew(n), s1, n);
}
