#include "ush.h"

static void change_export(char *arg, int len_n, char *name, char *value) {
    int i = 0;

    for (i = 0; arg[i] != '='; i++)
        name[i] = arg[i];
    for (i = 0; arg[len_n + i + 1] != '\0'; i++)
        value[i] = arg[len_n + i + 1];
}

int mx_export(char **args) {
    char *name = NULL;
    char *value = NULL;
    int len_n = 0;
    int len_v = 0;

    for (int y = 1; y < mx_count_arr_el(args); y++) {
        len_n = mx_get_char_index(args[y], '=');
        if (len_n != -1) {
            len_v = mx_strlen(args[y]) - len_n - 1;
            name = mx_strnew(len_n);
            value = mx_strnew(len_v);
            change_export(args[y], len_n, name, value);
            setenv(name, value, 1);
            mx_strdel(&name);
            mx_strdel(&value);
        }
    }
    return 0;
}

int mx_unset(char **args) {
    for (int y = 1; y < mx_count_arr_el(args); y++) {
        unsetenv(args[y]);
    }
    return 0;
}

int mx_fg(t_ush *ush) {
    if (ush->pids != NULL) {
        kill(ush->curr_pid, SIGCONT);
    }
    return 0;
}

