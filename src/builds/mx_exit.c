#include "ush.h"

int mx_exit(char **inp, int *exit_status) {
    int return_ = 0;

    if (mx_count_arr_el(inp) == 1) {
        mx_printstr("exit\n");
        *exit_status = 0;
    }
    else if (mx_atoi(inp[1]) == -2147483648
            && mx_count_arr_el(inp) == 2) {
        fprintf(stderr, "ush: exit: %s: numeric argument required\n", inp[1]);
        return_ = 1;
    }
    else if (mx_count_arr_el(inp) == 2) {
        *exit_status = mx_atoi(inp[1]);
        mx_printstr("exit\n");
    }
    else {
        fprintf(stderr, "ush: exit: too many arguments\n");
        return_ = 1;
    }
    return return_;
}
