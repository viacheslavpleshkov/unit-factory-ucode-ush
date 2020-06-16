#include "ush.h"

static void cd_err(char c, int *flag) {
    if (c != '\0')
        fprintf(stderr, MX_PWD_ERR, c);
    else
        fprintf(stderr, "pwd: too many arguments\n");
    *flag = 3;
}

static void parse_pwd(char **args, int *flag) {
    int len = mx_count_arr_el(args);

    for (int i = 1, stop = 0; i < len; i++) {
        if (mx_strcmp(args[i], "--") == 0)
            stop = 3;
        if (stop == 0 && args[i][0] == '-') {
            for (int y =1; y < mx_strlen(args[i]); y++) {
                if (args[i][y] != 'L' && args[i][y] != 'P') {
                    cd_err(args[i][y], flag);
                    break;
                }
            }
            if (*flag == 3)
                break;
            if((*flag = mx_find_flag("LP", args[i])) > 0)
                continue;
        }
        else
            cd_err('\0', flag);
    }
}


int mx_pwd(char **args, t_ush *ush) {
    int flag = 0;
    char *position = NULL;
    int is_link = 0;

    parse_pwd(args, &flag);
    if (flag != 2)
        position = mx_strdup(ush->pwd_l);
    else {
        position = MX_PWD();
        is_link = mx_check_symlink(&position, flag, 2);
    }
    if (flag != 3) {
        mx_printstr(position);
        mx_printchar('\n');
    }
    else {
        mx_strdel(&position);
        return 1;
    }
    mx_strdel(&position);
    return 0;
}
