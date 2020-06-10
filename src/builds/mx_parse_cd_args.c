#include "ush.h"

static void cd_print_error(char *arg, char *path) {
    if (mx_strcmp(arg, "-") != 0) {
        if (mx_file_exist(path) == 0)
            fprintf(stderr, "cd: no such file or directory: %s\n", arg);
        else
            fprintf(stderr, "cd: not a directory: %s\n", arg);
    }
}

static char *handle_path_value(char *arg, int *flag_recursion) {
    DIR *dp = NULL;
    char *path = NULL;

    if (arg[0] == '/')
        path = mx_strdup(arg);
    else
        path = mx_handle_path(arg, 0, flag_recursion);
    dp = opendir(path);
    if (dp != NULL) {
        closedir(dp);
        return path;
    }
    else if (dp == NULL)
        cd_print_error(arg,path);
    mx_strdel(&path);
    return NULL;
}

char *mx_parse_cd_args(char **args, int *flag, int len, int *flag_recursion) {
    char *arg = NULL;
    int stop = 0;

    if (len == 1 || (mx_strcmp(args[1], "--") == 0 && len == 2))
        arg = MX_HOME();
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
            arg = handle_path_value(args[i], flag_recursion);
            break;
        }
    }
    return arg;
}


