#include "ush.h"

void mx_write_to_pipe(char *str, int *fd) {
    close(fd[0]);
    write(fd[1], str, strlen(str));
    close(fd[1]);
}

void mx_read_from_pipe(char *str, int len, int *fd) {
    close(fd[1]);
    read(fd[0], str, len);
    close(fd[0]);
}

