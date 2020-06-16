#include "ush.h"

static int cd_print_error(char *path, t_ush *ush, char *value) {
    mx_setenv_ush(ush->pwd, ush);
    if (mx_file_exist(path) == 0)
        fprintf(stderr, "cd: no such file or directory: %s\n", path);
    else
        fprintf(stderr, "cd: not a directory: %s\n", path);
    mx_strdel(&value);
    return 1;
}

static char *previous_dir(t_ush *ush, int flag) {
    char *prev_dir = NULL;

    if (flag != 1)
        prev_dir = mx_strdup(ush->pwd_l);
    else
        prev_dir = MX_PWD();
    for (int i = mx_strlen(prev_dir) - 1; i >= 0; i--) {
        if (prev_dir[i] == '/') {
            prev_dir[i] = '\0';
            break;
        }
        prev_dir[i] = '\0';
    }
    if (mx_strlen(prev_dir) == 0) {
        mx_strdel(&prev_dir);
        prev_dir = mx_strdup("/");
    }
    return prev_dir;
}

static char *absolute_path(char *path, t_ush *ush) {
    char *tmp = NULL;
    char *value = NULL;

    if (mx_strcmp(ush->pwd_l, "/") != 0) {
        tmp = mx_strjoin(ush->pwd_l, "/");
        value = mx_strjoin(tmp, path);
        mx_strdel(&tmp);
    }
    else
        value = mx_strjoin("/", path);
    return value;
}

static int create_new_path(char **tokens, char *path, t_ush *ush, int flag) {
    char *value = NULL;

    for (int y = 0; tokens[y] != NULL; y++) {
        if (mx_strcmp(tokens[y], "..") == 0)
            value = previous_dir(ush, flag);
        else if (mx_strcmp(tokens[y], ".") == 0) {
            if (flag != 1)
                value = mx_strdup(ush->pwd_l);
            else
                value = MX_PWD();
        }
        else
            value = absolute_path(tokens[y], ush);
        if (chdir(value) != -1)
            mx_setenv_ush(value, ush);
        else
            return cd_print_error(path, ush, value);
        mx_strdel(&value);
    }
    return 0;
}

int mx_make_path(char *path, t_ush *ush, int flag) {
    char **tokens = mx_strsplit(path, '/');
    int ret = 0;

    ush->pwd = mx_strdup(ush->pwd_l);
    if (path[0] == '/') {
        chdir("/");
        mx_setenv_ush("/", ush);
    }
    if (tokens != NULL)
        ret = create_new_path(tokens, path, ush, flag);
    setenv("OLDPWD", ush->pwd, 1);
    mx_del_strarr(&tokens);
    mx_strdel(&ush->pwd);
    return ret;
}

