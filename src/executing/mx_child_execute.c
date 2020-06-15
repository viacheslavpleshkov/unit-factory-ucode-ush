#include "ush.h"

static void child_not_builtin(int *ret_val, char **input, char *command_p) {
    DIR *dp = NULL;
    extern char **environ;

    if ((dp = opendir(command_p)) != NULL) {
        fprintf(stderr, "ush: %s: is a directory\n", input[0]);
        *ret_val = 1;
        closedir(dp);
    }
    else if (mx_file_exist(command_p)) {
        int exec = execve(command_p, input, environ);
        if (exec == -1 && errno == EACCES) {
            fprintf(stderr, "ush: Permission denied:%s\n", input[0]);
            *ret_val = 1;
        }
    }
    else {
        fprintf(stderr, "ush: %s: command not found\n", input[0]);
        *ret_val = 1;
    }
}

static void child_free(char *command_p, int *fd, int ret_val) {
    char *ret = NULL;

    ret = mx_itoa(ret_val);
    mx_write_to_pipe(ret, fd);
    mx_strdel(&ret);
    mx_strdel(&command_p);
}

void mx_child_execute(int *ret, char **input, t_redirect *red, t_ush *ush) {
    char *command_p = mx_coomand_in_path(input[0], getenv("PATH"));
    int command = mx_is_builtin(command_p);

    mx_child_redirect(red);
    if (command == 2)
        *ret = mx_pwd(input);
    else if (command == 3)
        *ret = mx_env(input, ush);
    else if (command == 4)
        *ret = mx_ush(input, ush->ush_path);
    else if (command == 8)
        *ret = mx_which(input);
    else if (command == 9)
        *ret = mx_echo(input);
    else if (command == 0)
        child_not_builtin(ret, input, command_p);
    child_free(command_p, red->fd_return, *ret);
    exit(0);
}

