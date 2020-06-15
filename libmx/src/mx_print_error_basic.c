#include "libmx.h"

void mx_print_error_basic(const char *str) {
    write(2, str, mx_strlen(str));
}
