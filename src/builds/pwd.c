#include "ush.h"

void pwd() {
    char *path = mx_strnew(PATH_MAX);

    path = getwd(path);
    printf("%s\n", path);
    mx_strdel(&path);
}
