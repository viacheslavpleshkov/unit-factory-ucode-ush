#include "ush.h"

static char *find_ush_path(char **commands) {
    char *pwd = MX_PWD();
    char *ush_path = NULL;

    if (mx_strstr(commands[0], "./"))
        ush_path = mx_replace_substr(commands[0], ".", pwd);
    else
        ush_path = mx_strdup(commands[0]);
    mx_strdel(&pwd);
    return ush_path;
}

static t_dbl_list* lst_create() {
    t_dbl_list *lst = (t_dbl_list*) malloc(sizeof (t_dbl_list));

    lst->data = NULL;
    lst->next = NULL;
    lst->prev = NULL;
    return lst;
}

t_ush* mx_create_ush(char **argv) {
    t_ush *ush = (t_ush *)malloc(sizeof(t_ush));

    ush->command = NULL;
    ush->history = NULL;
    ush->emodji_num = 128512;
    ush->exit_status = -1;
    ush->return_value = 0;
    ush->exit_non_term = 0;
    ush->pids = NULL;
    ush->str_input = NULL;
    ush->ush_path = find_ush_path(argv);
    ush->history = lst_create();
    return ush;
}
void mx_set_shl(void) {
    char *shlv = MX_SHLVL();
    char *shlvl = mx_itoa(mx_atoi(shlv) + 1);
    extern char **environ;
    char cwd[PATH_MAX];

    if (getenv("PWD") == NULL) {
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            setenv("PWD", cwd, 1);
    }
    if (getenv("SHLVL") == NULL)
        setenv("SHLVL", "1", 1);
    else
        setenv("SHLVL", shlvl, 1);
    if (getenv("_") == NULL)
        setenv("_", "/usr/bin/env", 1);
    mx_strdel(&shlvl);
    mx_strdel(&shlv);
}
