#include "ush.h"

static int is_comm_rw(char *str) {
    char reserved_words[][5] = {"!", "{", "}", "time"};

    for (int i = 0; i < 4; i++) {
        if (strcmp(str, reserved_words[i]) == 0)
            return 1;
    }
    return -1;
}

static void check_builtin(char *input, int *ret_flag, int flag) {
    char *tmp = NULL;

    tmp = mx_coomand_in_path(input, MX_PATH());
    if (mx_is_builtin(tmp) != 0) {
        if (flag != 1)
            printf("%s: shell built-in command\n", input);
        if (flag == 2 && strcmp(tmp, input) != 0)
            printf("%s\n", tmp);
    }
    else if (strcmp(tmp, input) != 0) {
        if (flag != 1)
            printf("%s\n", tmp);
    }
    else
        *ret_flag = 1;
    mx_strdel(&tmp);
}

static void check_command(char *input, int *ret_flag, int flag) {
    char **path = NULL;

    if (is_comm_rw(input) == 1)
        printf("%s: shell reserved word\n", input);
    else if (mx_get_char_index(input, '/') != -1) {
        path = mx_strsplit(MX_PATH(), ':');
        for (int y = 0; y < mx_count_arr_el(path); y++) {
            if (mx_get_substr_index(input, path[y]) != -1
                && mx_file_exist(input)) {
                if (flag != 1)
                    printf("%s\n", input);
                *ret_flag = 0;
                break;
            }
            *ret_flag = 1;
        }
        mx_free_void_arr((void**)path, mx_count_arr_el(path));
    }
    else
        check_builtin(input, ret_flag, flag);
}

static int check_flag(char *input, int *flag) {
    for (int y = 1; y < mx_strlen(input); y++) {
        if (input[y] == 's' && *flag != 2)
            *flag = 1;
        else if (input[y] == 'a')
            *flag = 2;
        else {
            fprintf(stderr, MX_WHICH_US, input[y]);
            return 1;
        }
    }
    return 0;
}

int mx_which(char **input) {
    int flag = 0;
    int ret_flag = 0;

    if (mx_count_arr_el(input) == 1) {
        fprintf(stderr, "usage: which [-as] program ...\n");
        return 1;
    }
    for (int i = 1; i < mx_count_arr_el(input); i++) {
        if (strcmp(input[i], "--") == 0)
            flag = 3;
        else if (input[i][0] == '-' && flag < 3) {
            if ((ret_flag = check_flag(input[i], &flag)) == 0)
                continue;
        }
        check_command(input[i], &ret_flag, flag);
    }
    return ret_flag;
}


