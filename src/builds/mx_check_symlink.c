#include "ush.h"

static void path_symlink(char **arg) {
    char buf[1024];
    ssize_t len = 0;

    if ((len = readlink(*arg, buf, 1024)) == -1)
        perror("readlink");
    buf[len] = '\0';
    mx_strdel(arg);
    if (buf[0] != '.')
        *arg = mx_strjoin("/", buf);
    else
        *arg = mx_strdup(buf);
}

int mx_check_symlink(char **arg, int flag, int link) {
    struct stat *st = (struct stat *) malloc(sizeof (struct stat));
    int is_link = 0;

    lstat(*arg, st);
    if ((st->st_mode & S_IFMT) == S_IFLNK) {
        is_link = 1;
        if (flag == link)
            path_symlink(arg);
    }
    if (st != NULL) {
        free(st);
        st = NULL;
    }
    return is_link;
}

