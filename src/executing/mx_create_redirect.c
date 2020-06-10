#include "ush.h"

void mx_free_execute(t_redirect *redirect, char **input) {
    mx_strdel(&redirect->_stderr);
    mx_strdel(&redirect->_stdout);
    free(redirect);
    mx_free_void_arr((void**)input, mx_count_arr_el(input));
}

t_redirect *mx_create_redirect(int flag_redir) {
    t_redirect *redirect = (t_redirect *)malloc(sizeof(t_redirect));
    redirect->_stderr = mx_strnew(1000);///
    redirect->_stdout = mx_strnew(1000);///
    redirect->flag = flag_redir;
    pipe(redirect->fd_return);
    pipe(redirect->fd_stdout);
    pipe(redirect->fd_stderr);
    return redirect;
}

void mx_parent_redirect(t_redirect *redirect, int *return_) {
    if (redirect->flag == 1)
        mx_read_from_pipe(redirect->_stdout, 1000, redirect->fd_stdout);
    mx_read_from_pipe(redirect->_stderr, 1000, redirect->fd_stderr);
    if (mx_strlen(redirect->_stderr) != 0) {
        *return_ = 1;
        mx_printstr(redirect->_stderr);
    }
}

void mx_child_redirect(t_redirect *redirect) {
    if (redirect->flag == 1) {
        if (dup2(redirect->fd_stdout[1], 1) == -1)
            perror("dup2");
        close(redirect->fd_stdout[0]);
    }
    if (dup2(redirect->fd_stderr[1], 2) == -1)
        perror("dup2");
    close(redirect->fd_stderr[1]);
}

