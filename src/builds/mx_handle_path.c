#include "ush.h"

static char *previous_dir(void) {
    char *prev_dir = MX_PWD();

    for (int i = mx_strlen(prev_dir) - 1; i >= 0; i--) {
        if (prev_dir[i] == '/') {
            prev_dir[i] = '\0';
            break;
        }
        prev_dir[i] = '\0';
    }
    return prev_dir;
}


static char *elseif_1(char *value, char *path, int *fl_rec) {
    char *pwd = MX_PWD();
    *fl_rec = 1;
    setenv("OLDPWD", pwd, 1);
    for (int y = 0; y < mx_count_substr(path, "..") - 1; y ++) {
        value = previous_dir();
        if (chdir(value) != -1)
            setenv("PWD", value, 1);
        mx_strdel(&value);
    }
    value = previous_dir();
    mx_strdel(&pwd);
    return value;
}

static char *elseif_2(char *value, char *path, int i) {
    value = MX_PWD();
    value = mx_realloc(value, mx_strlen(value) + mx_strlen(path) + 2);
    for (; i < mx_strlen(path); i++)
        value[mx_strlen(value) + i] = path[i + 1];
    value[mx_strlen(value) + i] = '\0';
    return value;
}

static char *elseif(char *path) {
    char *pwd = MX_PWD();
    char *tmp = NULL;
    char *value = NULL;

    tmp = mx_strjoin(pwd, "/");
    value = mx_strjoin(tmp, path);
    mx_strdel(&tmp);
    mx_strdel(&pwd);
    return value;
}
char *mx_handle_path(char *path, int i, int *fl_rec) {
    char *value = NULL;
    if (mx_strcmp(path, "-") == 0) {
        if (MX_OLDPWD() != NULL)
            value = mx_strdup(MX_OLDPWD());
        else
            fprintf(stderr, "ush: cd: OLDPWD not set\n");
    }
    else if (mx_count_substr(path, "..") > 0)
        value = elseif_1(value, path, fl_rec);
    else if (path[0] != '.')
        value = elseif(path);
    else if (mx_strcmp(path, ".") != 0)
        elseif_2(value, path, i);
    else if (mx_strcmp(path, ".") == 0)
        value = MX_PWD();
    return value;
}
