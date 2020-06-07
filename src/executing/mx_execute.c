#include "ush.h"

static int par_exec_command(char *command_p, char **input, int *exit_status) {
    int command = mx_is_builtin(command_p);
    int ret_val = 0;

    if (command == 1)
        ret_val = mx_cd(input);
    else if (command == 5)
        ret_val = mx_export(input);
    else if (command == 6)
        ret_val = mx_unset(input);
    else if (command == 7)
        ret_val = mx_exit(input, exit_status);
    return ret_val;
}

static void par_execute(int *ret_val, int *fd, char **input, int *exit_status) {
    char *command_p = mx_coomand_in_path(input[0], MX_PATH());
    char *ret_str = mx_strnew(1);
    int status = 0;

    *ret_val = par_exec_command(command_p, input, exit_status);
    waitpid(-1, &status, WUNTRACED);
    mx_read_from_pipe(ret_str, 1, fd);
    if (mx_atoi(ret_str) == 1 || *ret_val == 1)
        *ret_val = 1;
    else
        *ret_val = 0;
    mx_strdel(&ret_str);
    mx_strdel(&command_p);
}

int mx_execute(t_ush *ush, char *str_input, int flag_redirect) {
    pid_t pid;
    int return_ = 0;
    char **input = mx_check_expansion(str_input, ush->return_value);
    t_redirect *redirect = mx_create_redirect();

    pid = fork();
    if (pid != 0) {
        par_execute(&return_, redirect->fd_return, input, &ush->exit_status);
        mx_parent_redirect(flag_redirect, redirect, &return_);
    }
    else {
        signal(SIGTSTP, SIG_DFL);
        mx_child_redirect(flag_redirect, redirect);
        mx_child_execute(&return_, input, redirect->fd_return, ush);
    }
    mx_strdel(&redirect->_stderr);
    mx_strdel(&redirect->_stdout);
    free(redirect);
    mx_free_void_arr((void**)input, mx_count_arr_el(input));
    return return_;
}
