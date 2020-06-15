#include "ush.h"

static int par_exec_command(char **input, t_ush *ush, pid_t pid) {
    char *command_p = mx_coomand_in_path(input[0], MX_PATH());
    int command = mx_is_builtin(command_p);
    int ret_val = 0;

    ush->curr_pid = pid;
    if (command == 1)
        ret_val = mx_cd(input);
    else if (command == 5)
        ret_val = mx_export(input);
    else if (command == 6)
        ret_val = mx_unset(input);
    else if (command == 7)
        ret_val = mx_exit(input, &ush->exit_status);
    mx_strdel(&command_p);
    return ret_val;
}

static void fill_jobs(pid_t pid, t_ush *ush) {
    t_pid *temp = NULL;
    if (ush->pids != NULL) {
        temp = ush->pids;
        ush->pids = ush->pids->next;
    }
    ush->pids = (t_pid *) malloc(sizeof (t_pid));
    ush->pids->num = pid;
    ush->pids->index++;
    ush->pids->str = mx_strdup(ush->str_input);
    ush->pids->prev = temp;
    ush->pids->next = NULL;
}

static void free_jobs(t_ush *ush) {
    char **input = mx_strsplit(ush->str_input, ' ');
    t_pid *temp = NULL;

    if (mx_strcmp(input[0], "fg") == 0 && ush->pids != NULL) {
        mx_strdel(&ush->str_input);
        ush->curr_pid = ush->pids->num;
        ush->str_input = mx_strdup(ush->pids->str);
        temp = ush->pids;
        ush->pids = ush->pids->prev;
        mx_strdel(&temp->str);
        free(temp);
    }
    mx_free_void_arr((void **) input, mx_count_arr_el(input));
}

static void check_for_redir(int *ret, int *fd, t_redirect *red, t_ush *ush) {
    char *ret_str = mx_strnew(1);
    int status = 0;

    free_jobs(ush);
    waitpid(ush->curr_pid, &status, WUNTRACED);
    if(!WIFSTOPPED(status)) {
        mx_read_from_pipe(ret_str, 1, fd);
        mx_parent_redirect(red, ret);
    }
    if(WIFSTOPPED(status)) {
        *ret = 146;
        printf("\nush: suspended  %s\n", ush->str_input);
        fill_jobs(ush->curr_pid, ush);
    }
    else if (mx_atoi(ret_str) == 1 || *ret == 1)
        *ret = 1;
    else
        *ret = 0;
    mx_strdel(&ret_str);
}

int mx_execute(t_ush *ush, char *str_input, int flag_redir, char **str_red) {
    pid_t pid;
    int return_ = 0;
    char **input = mx_check_expansion(str_input, ush->return_value);
    t_redirect *redirect = mx_create_redirect(flag_redir);
    ush->str_input = str_input;

    pid = fork();
    if (pid != 0) {
        return_ = par_exec_command(input, ush, pid);
        check_for_redir(&return_, redirect->fd_return, redirect, ush);
    }
    else
        mx_child_execute(&return_, input, redirect, ush);
    if (redirect->_stdout != NULL && flag_redir == 1) {
        if (redirect->_stdout[mx_strlen(redirect->_stdout) - 1] == '\n')
            redirect->_stdout[mx_strlen(redirect->_stdout) - 1] = '\0';
        *str_red = mx_strdup(redirect->_stdout);
    }
    mx_free_execute(redirect, input);
    return return_;
}
