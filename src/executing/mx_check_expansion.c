#include "ush.h"


static char *dollar_change(int len, char **input) {
    char *variable = NULL;

    if ((*input)[1] == '{' && (*input)[len - 1] == '}') {
        variable = mx_strnew(len - 1);
        for (int y = 2, x = 0; y < len - 1; y++, x++)
            variable[x] = (*input)[y];
        variable[len - 3] = '=';
        variable[len - 2] = '\0';
    }
    else {
        variable = mx_strnew(len + 1);
        for (int y = 1, x = 0; y < len; y++, x++)
            variable[x] = (*input)[y];
        variable[len - 1] = '=';
        variable[len] = '\0';
    }
    return variable;
}

static void insert_str(char **in, int j, char *var) {
    int x = 0;
    extern char **environ;

    mx_strdel(in);
    (*in) = mx_strnew(mx_strlen(environ[j]) - mx_strlen(var) + 1);
    x = 0;
    for (int y = mx_strlen(var); y <= mx_strlen(environ[j]); y++)
        (*in)[x++] = environ[j][y];
    (*in)[x] = '\0';
}

static void dollar_check(int len, char **in) {
    char *var = NULL;
    extern char **environ;
    int flag = 0;

    var = dollar_change(len, in);
    for (int j = 0; environ[j]!= NULL; j++) {
        if (strstr(environ[j], var) != NULL && environ[j][0] == var[0]) {
            flag = 1;
            insert_str(in, j, var);
            break;
        }
    }
    mx_strdel(&var);
    if (flag == 0) {
        mx_strdel(in);
        (*in) = mx_strdup("");
    }
}

char **mx_check_expansion(char *str_input, int ret_val) {
    int len = 0;
    char **input = mx_strsplit(str_input, ' ');
    int check = mx_check_echo(input);

    if (check != 0) {
        mx_free_void_arr((void **)input, mx_count_arr_el(input));
        input = mx_split_echo(str_input, check);
    }
    for (int i = 0; i < mx_count_arr_el(input); i++) {
        if (mx_get_substr_index(input[i], "$?") >= 0) {
            mx_strdel(&input[i]);
            input[i] = mx_itoa(ret_val);
        }
        if (input[i][0] == '~')
            mx_tidle_check(&input[i]);
        len = mx_strlen(input[i]);
        if (input[i][0] == '$')
            dollar_check(len, &input[i]);
    }
    return input;
}
