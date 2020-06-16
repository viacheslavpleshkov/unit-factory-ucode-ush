#include "ush.h"

void mx_setenv_ush(char *arg, t_ush *ush) {
    if (mx_strlen(arg) != 1 && arg[mx_strlen(arg) - 1] == '/')
        arg[mx_strlen(arg) - 1] = '\0';
    if (mx_strcmp(arg, ush->pwd_l) != 0) {
        mx_strdel(&ush->pwd_l);
        ush->pwd_l = mx_strdup(arg);
    }
    setenv("PWD", arg, 1);
}

static void oldpwd(t_ush *ush) {
    mx_setenv_ush(MX_OLDPWD(), ush);
    setenv("OLDPWD", ush->pwd_l, 1);
}

static int handle_path(char *path, int flag, t_ush *ush) {
    int ret = 0;
    char *tmp = mx_strdup(path);
    int link = mx_check_symlink(&tmp, flag, 1);

    if (flag == 2 && link == 1) {
        fprintf(stderr, "cd: not a directory: %s\n", path);
        ret = 1;
    }
    else if (mx_strcmp(tmp, "-") == 0) {
        if (MX_OLDPWD() != NULL)
            oldpwd(ush);
        else {
            fprintf(stderr, "ush: cd: OLDPWD not set\n");
            ret = 1;
        }
    }
    else
        ret = mx_make_path(tmp, ush, flag);
    mx_strdel(&tmp);
    return ret;
}

static void stay_here(t_ush *ush) {
    char *arg = MX_HOME();

    setenv("OLDPWD", ush->pwd_l, 1);
    mx_setenv_ush(arg, ush);
    mx_strdel(&arg);
}

int mx_cd(char **args, t_ush *ush) {
    int stop = 0;
    int len = mx_count_arr_el(args);
    int flag = 0;

    if (len == 1 || (mx_strcmp(args[1], "--") == 0 && len == 2))
        stay_here(ush);
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
            return handle_path(args[i], flag, ush);
        }
    }
    return 0;
}
