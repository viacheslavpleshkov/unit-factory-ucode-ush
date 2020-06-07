#include "ush.h"

static void parse_pwd(char **args, int *flag) {
    int len = mx_count_arr_el(args);
    int stop = 0;

    for (int i = 1; i < len; i++) {
        if (mx_strcmp(args[i], "--") == 0)
            stop = 3;
        if (stop == 0 && args[i][0] == '-') {
            for (int y =1; y < mx_strlen(args[i]); y++) {
                if (args[i][y] != 'L' && args[i][y] != 'P') {
                    fprintf(stderr, MX_PWD_ERR, args[i][y]);
                    *flag = 3;
                    break;
                }
            }
            if (*flag == 3)
                break;
            if((*flag = mx_find_flag("LP", args[i])) > 0)
                continue;
        }
    }
}


int mx_pwd(char **args) {
    int flag = 0;
    char *position = mx_strdup(MX_PWD());
    int is_link = 0;

    parse_pwd(args, &flag);
    is_link = mx_check_symlink(position, flag, 2);
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
