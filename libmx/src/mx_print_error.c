#include "libmx.h"

void mx_print_error(const char *str, int exit_code, bool exit_status) {
    write(2, str, mx_strlen(str));
    write(2, "\n", 1);
    if (exit_status)
        exit(exit_code);
}
