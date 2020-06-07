#include "ush.h"

static char *previous_dir(void) {
    char *prev_dir = mx_strdup(MX_PWD());
    for (int i = mx_strlen(prev_dir) - 1; i >= 0; i--) {
        if (prev_dir[i] == '/') {
            prev_dir[i] = '\0';
            break;
        }
        prev_dir[i] = '\0';
    }
    return prev_dir;
}

static char *handle_path(char *path, int i) {
    char *value = NULL;
    char *tmp = NULL;

    if (mx_strcmp(path, "-") == 0)
        value = mx_strdup(MX_OLDPWD());
    else if (mx_strcmp(path, "..") == 0)
        value = previous_dir();
    else if (path[0] != '.') {
        tmp = mx_strjoin(MX_PWD(), "/");
        value = mx_strjoin(tmp, path);
        mx_strdel(&tmp);
    }
    else if (mx_strcmp(path, ".") != 0) {
        value = mx_strdup(MX_PWD());
        value = mx_realloc(value, mx_strlen(value) + mx_strlen(path) + 2);
        for (; i < mx_strlen(path); i++)
            value[mx_strlen(value) + i] = path[i + 1];
        value[mx_strlen(value) + i] = '\0';
    }
    return value;
}

static void cd_print_error(char **args, int i, char *path) {
    if (mx_file_exist(path) == 0)
        fprintf(stderr, "cd: no such file or directory: %s\n", args[i]);
    else
        fprintf(stderr, "cd: not a directory: %s\n", args[i]);
}

static char *handle_path_value(char **args, int index) {
    DIR *dp = NULL;
    char *path = NULL;

    if (args[index][0] == '/')
        path = mx_strdup(args[index]);
    else
        path = handle_path(args[index], 0);
    dp = opendir(path);
    if (dp != NULL) {
        closedir(dp);
        return path;
    }
    else if (dp == NULL)
        cd_print_error(args, index, path);
    mx_strdel(&path);
    return NULL;
}

char *mx_parse_cd_args(char **args, int *flag, int len) {
    char *arg = NULL;
    int stop = 0;

    if (len == 1 || (mx_strcmp(args[1], "--") == 0 && len == 2))
        arg = mx_strdup(MX_HOME());
    else {
        for (int i = 1; i < len; i++) {
            if (mx_strcmp(args[i], "--") == 0) {
                stop = 3;
                continue;
            }
            if (stop == 0 && args[i][0] == '-') {
                if ((*flag = mx_find_flag("Ps", args[i])) > 0)
                    continue;
            }
            arg = handle_path_value(args, i);
            break;
        }
    }
    return arg;
}


