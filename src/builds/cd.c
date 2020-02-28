#include "ush.h"

static char *find_path(char *pathName, char *file, int flag) {
    char *p = NULL;

    if (flag == 1) {
        if (mx_strchr(file, '/') == NULL) {
            p = mx_strdup("./");
            p = mx_realloc(p, sizeof (char) * (mx_strlen(file) + 3));
            p = mx_strcat(p, file);
        }
        else
            p = mx_strdup(file);
    }
    else {
        p = mx_strdup(pathName);
        p = mx_realloc(p, sizeof (char) * (mx_strlen(p) + 2));
        if (mx_strcmp(pathName, "/") != 0)
            p = mx_strcat(p, "/");
        p = mx_realloc(p, sizeof (char) * (mx_strlen(p) + mx_strlen(file) + 1));
        p = mx_strcat(p, file);
    }
    return p;
}

static int file_exist(char *file) {
    struct stat *st = (struct stat*) malloc(sizeof (struct stat));
    int flag = 0;
    char *path = find_path(NULL, file, 1);

    if ((lstat(path, st) != -1))
        flag = 1;
    free(st);
    st = NULL;
    mx_strdel(&path);
    return flag;
}

static int cd_errors(char **input) {
    DIR *dp = NULL;

    if (mx_count_arr_el(input) > 2)
        fprintf(stderr, "cd: string not in pwd: %s\n", input[1]);
    for (int i = 1; i < mx_count_arr_el(input); i++) {
        if (input[i][0] == '-') {
            if (mx_strcmp(input[i], "-") == 0)
                return 0;
        }
        else if (file_exist(input[i]) == 0)
            fprintf(stderr, "cd: no such file or directory: %s\n", input[i]);
        else if ((dp = opendir(input[i])) == NULL)
            fprintf(stderr, "cd: not a directory: %s\n", input[i]);
        else {
            if (dp != NULL)
                closedir(dp);
            return 0;
        }
    }
    return 1;
}

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

static char *handle_value(char *path) {
    char *value = NULL;
    int i = 0;

    if (path[0] == '/')
        value = mx_strdup(path);
    else {
        value = mx_strdup(MX_PWD());
        value = mx_realloc(value, mx_strlen(value) + mx_strlen(path) + 2);
        if (path[0] != '.' && mx_strcmp(path, "-") != 0) {
            mx_strcat(value, "/");
            mx_strcat(value, path);
        }
        else if (mx_strcmp(path, ".") != 0 && mx_strcmp(path, "..") != 0 && mx_strcmp(path, "-") != 0) {
            for (; i < mx_strlen(path); i++)
                value[mx_strlen(value) + i] = path[i + 1];
            value[mx_strlen(value) + i] = '\0';
        }
        else if (mx_strcmp(path, "..") == 0 || mx_strcmp(path, "-") == 0)
            value = previous_dir();
    }
    return value;
}

void cd(char **input) {
    char *value = NULL;
    int err = cd_errors(input);

    if (err == 0) {
        if (input[1] != NULL) {
            value = handle_value(input[1]);
            if (chdir(value) != -1) {
                setenv("PWD", value, 1);
            }
        } else {
            chdir(MX_HOME());
            setenv("PWD", MX_HOME(), 1);
        }
        mx_strdel(&value);
    }
}
