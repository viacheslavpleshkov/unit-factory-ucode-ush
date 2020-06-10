#include "ush.h"

static void if_tidle(char **inp, char *home, char *pwd) {
    char *tmp = mx_strdup(*inp);

    if (mx_isalpha((*inp)[1])) {
        mx_strdel(inp);
        *inp = mx_replace_substr(tmp, "~", "/Users/");
    }
    else if ((*inp)[1] == '/' || (*inp)[1] == '\0') {
        mx_strdel(inp);
        *inp = mx_replace_substr(tmp, "~", home);
    }
    else if ((*inp)[1] == '+' && ((*inp)[2] == '/' || (*inp)[2] == '\0')) {
        mx_strdel(inp);
        *inp = mx_replace_substr(tmp, "~+", pwd);
    }
    else if ((*inp)[1] == '-' && ((*inp)[2] == '/' || (*inp)[2] == '\0')) {
        if (MX_OLDPWD() != NULL) {
            mx_strdel(inp);
            *inp = mx_replace_substr(tmp, "~-", MX_OLDPWD());
        }
    }
    mx_strdel(&tmp);
}
static char *tidle_check(char *input) {//temporary for all
    char *home = mx_strdup("");
    char *pwd = MX_PWD();

    if (getenv("HOME") != NULL) {
        mx_strdel(&home);
        home = MX_HOME();
    }
    if_tidle(&input, home, pwd);
    mx_strdel(&home);
    mx_strdel(&pwd);
    return input;
}

static char *dollar_change(int len, char *input) {
    char *variable = NULL;

    if (input[1] == '{' && input[len - 1] == '}') {
        variable = mx_strnew(len - 2);
        for (int y = 2, x = 0; y < len - 1; y++, x++)
            variable[x] = input[y];
        variable[len - 3] = '=';
    }
    else {
        variable = mx_strnew(len);
        for (int y = 1, x = 0; y < len; y++, x++)
            variable[x] = input[y];
        variable[len - 1] = '=';
    }
    return variable;
}

static char *dollar_check(int len, char *in) {
    char *var = NULL;
    extern char **environ;
    int x = 0;
    int flag = 0;

    var = dollar_change(len, in);
    for (int j = 0; environ[j]!= NULL; j++) {
        if (strstr(environ[j], var) != NULL) {
            flag = 1;
            in = realloc(in, mx_strlen(environ[j]) - mx_strlen(var) + 1);
            x = 0;
            for (int y = mx_strlen(var); y <= mx_strlen(environ[j]); y++)
                in[x++] = environ[j][y];
        }
    }
    mx_strdel(&var);
    if (flag == 0) {
        mx_strdel(&in);
        in = mx_strdup("");
    }
    return in;
}

char **mx_check_expansion(char *str_input, int ret_val) {
    int len = 0;
    char **input = mx_strsplit(str_input, ' ');

    for (int i = 0; i < mx_count_arr_el(input); i++) {
        if (mx_get_substr_index(input[i], "$?") >= 0) {
            mx_strdel(&input[i]);
            input[i] = mx_itoa(ret_val);
        }
        if (input[i][0] == '~')
            input[i] = tidle_check(input[i]);
        len = mx_strlen(input[i]);
        if (input[i][0] == '$')
            input[i] = dollar_check(len, input[i]);
    }
    return input;
}
