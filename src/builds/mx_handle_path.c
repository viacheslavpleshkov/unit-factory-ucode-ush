#include "ush.h"

static void cd_print_error(char *path) {
    if (mx_file_exist(path) == 0)
        fprintf(stderr, "cd: no such file or directory: %s\n", path);
    else
        fprintf(stderr, "cd: not a directory: %s\n", path);
}

static char *previous_dir(void) {
    char *prev_dir = MX_PWD();

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

static char *absolute_path(char *path) {
    char *pwd = MX_PWD();
    char *tmp = NULL;
    char *value = NULL;

    if (mx_strcmp(pwd, "/") != 0) {
        tmp = mx_strjoin(pwd, "/");
        value = mx_strjoin(tmp, path);
        mx_strdel(&tmp);
        mx_strdel(&pwd);
    }
    else
        value = mx_strjoin("/", path);
    mx_strdel(&pwd);
    return value;
}

static int create_new_path(char **tokens, char *path, char *pwd) {
    char *value = NULL;

    for (int y = 0; tokens[y] != NULL; y++) {
        if (mx_strcmp(tokens[y], "..") == 0)
            value = previous_dir();
        else if (mx_strcmp(tokens[y], ".") == 0)
            value = MX_PWD();
        else
            value = absolute_path(tokens[y]);
        if (chdir(value) != -1)
            mx_setenv_ush(value);
        else {
            setenv("PWD", pwd, 1);
            cd_print_error(path);
            mx_strdel(&value);
            return 1;
        }
        mx_strdel(&value);
    }
    return 0;
}

int mx_make_path(char *path) {
    char *pwd = MX_PWD();
    char **tokens = mx_strsplit(path, '/');
    int ret = 0;

    if (path[0] == '/') {
        chdir("/");
        setenv("PWD", "/", 1);
    }
    if (tokens != NULL)
        ret = create_new_path(tokens, path, pwd);
    setenv("OLDPWD", pwd, 1);
    mx_strdel(&pwd);
    mx_del_strarr(&tokens);
    return ret;
}

