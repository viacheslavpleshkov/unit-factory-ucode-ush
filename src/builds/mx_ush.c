#include "ush.h"

int mx_ush(char **input, char *ush_path) {
    extern char **environ;

    mx_strdel(&input[0]);
    input[0] = mx_strdup(ush_path);
    if (execve(ush_path, input, environ) != -1)
        return 0;
    else
        return 1;
}
