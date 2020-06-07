#include "ush.h"

t_redirect *mx_create_redirect(void) {
    t_redirect *redirect = (t_redirect *)malloc(sizeof(t_redirect));
    redirect->_stderr = mx_strnew(1000);
    redirect->_stdout = mx_strnew(1000);
    pipe(redirect->fd_return);
    pipe(redirect->fd_stdout);
    pipe(redirect->fd_stderr);
    return redirect;
}

void mx_parent_redirect(int flag_redir, t_redirect *redirect, int *return_) {
    if (flag_redir == 1)
        mx_read_from_pipe(redirect->_stdout, 1000, redirect->fd_stdout);
    mx_read_from_pipe(redirect->_stderr, 1000, redirect->fd_stderr);
    if (mx_strlen(redirect->_stderr) != 0) {
        *return_ = 1;
        mx_printstr(redirect->_stderr);
    }
}

void mx_child_redirect(int flag_redirect, t_redirect *redirect) {
    if (flag_redirect == 1) {
        if (dup2(redirect->fd_stdout[1], 1) == -1)
            perror("dup2");
        close(redirect->fd_stdout[0]);
    }
    if (dup2(redirect->fd_stderr[1], 2) == -1)
        perror("dup2");
    close(redirect->fd_stderr[1]);
}

