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

static void child_free(char *ret, char *command_p) {
    mx_strdel(&ret);
    mx_strdel(&command_p);
}

void mx_child_execute(int *ret_val, char **input, int *fd, t_ush *ush) {
    char *command_p = mx_coomand_in_path(input[0], MX_PATH());
    int command = mx_is_builtin(command_p);
    char *ret = NULL;

    if (command == 2)
        *ret_val = mx_pwd(input);
    else if (command == 3)
        *ret_val = mx_env(input, ush);
    else if (command == 4)
        *ret_val = mx_ush(input, ush->ush_path);
    else if (command == 8)
        *ret_val = mx_which(input);
    else if (command == 9)
        *ret_val = mx_echo(input);
    else if (command == 0)
        child_not_builtin(ret_val, input, command_p);
    ret = mx_itoa(*ret_val);
    mx_write_to_pipe(ret, fd);
    child_free(ret, command_p);
    exit(0);
}

