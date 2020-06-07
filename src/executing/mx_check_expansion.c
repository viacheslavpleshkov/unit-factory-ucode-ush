#include "ush.h"

static char *tidle_check(char *input) {
    char *tmp = mx_strdup(input);

    if (mx_isalpha(input[1])) {
        mx_strdel(&input);
        input = mx_replace_substr(tmp, "~", "/Users/");
    }
    else if (input[1] == '/' || input[1] == '\0') {
        mx_strdel(&input);
        input = mx_replace_substr(tmp, "~", MX_HOME());
    }
    else if (input[1] == '+' && (input[2] == '/' || input[2] == '\0')) {
        mx_strdel(&input);
        input = mx_replace_substr(tmp, "~+", MX_PWD());
    }
    else if (input[1] == '-' && (input[2] == '/' || input[2] == '\0')) {
        mx_strdel(&input);
        input = mx_replace_substr(tmp, "~-", MX_OLDPWD());
    }
    mx_strdel(&tmp);
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

    var = dollar_change(len, in);
    for (int j = 0; environ[j]!= NULL; j++) {
        if (strstr(environ[j], var) != NULL) {
            in = realloc(in, mx_strlen(environ[j]) - mx_strlen(var) + 1);
            x = 0;
            for (int y = mx_strlen(var); y <= mx_strlen(environ[j]); y++)
                in[x++] = environ[j][y];
        }
    }
    mx_strdel(&var);
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
