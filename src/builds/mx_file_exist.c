#include "ush.h"

int mx_file_exist(char *path) {
    struct stat *st = (struct stat*) malloc(sizeof (struct stat));
    int flag = 0;

    if ((lstat(path, st) != -1))
        flag = 1;
    if (st != NULL) {
        free(st);
        st = NULL;
    }
    return flag;
}
