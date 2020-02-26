#include "libmx.h"

void mx_printstr(const char *s) {
    if (!s)
        return;
    write(1, s, mx_strlen(s));
}
