#include "ush.h"

void mx_setenv_ush(char *arg) {
    char *pwd = MX_PWD();

    if (mx_strlen(arg) != 1 && arg[mx_strlen(arg) - 1] == '/')
        arg[mx_strlen(arg) - 1] = '\0';
    setenv("PWD", arg, 1);
    mx_strdel(&pwd);
}

static void oldpwd(void) {
    char *pwd = MX_PWD();

    mx_setenv_ush(MX_OLDPWD());
    setenv("OLDPWD", pwd, 1);
    mx_strdel(&pwd);
}

static int handle_path(char *path, int flag) {
    int ret = 0;
    char *tmp = mx_strdup(path);
    int link = mx_check_symlink(&tmp, flag, 1);

    if (flag == 2 && link == 1) {
        fprintf(stderr, "cd: not a directory: %s\n", path);
        ret = 1;
    }
    else if (mx_strcmp(tmp, "-") == 0) {
        if (MX_OLDPWD() != NULL)
            oldpwd();
        else {
            fprintf(stderr, "ush: cd: OLDPWD not set\n");
            ret = 1;
        }
    }
    else
        ret = mx_make_path(tmp);
    mx_strdel(&tmp);
    return ret;
}

static void stay_here(void) {
    char *arg = MX_HOME();
    char *pwd = MX_PWD();

    setenv("OLDPWD", pwd, 1);
    mx_setenv_ush(arg);
    mx_strdel(&pwd);
    mx_strdel(&arg);
}

int mx_cd(char **args) {
    int stop = 0;
    int len = mx_count_arr_el(args);
    int flag = 0;

    if (len == 1 || (mx_strcmp(args[1], "--") == 0 && len == 2))
        stay_here();
    else {
        for (int i = 1; i < len; i++) {
            if (mx_strcmp(args[i], "--") == 0) {
                stop = 3;
                continue;
            }
            if (stop == 0 && args[i][0] == '-') {
                if ((flag = mx_find_flag("Ps", args[i])) > 0)
                    continue;
            }
            return handle_path(args[i], flag);
        }
    }
    return 0;
}
