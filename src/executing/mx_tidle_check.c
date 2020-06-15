#include "ush.h"

static void tidle_replace(char **inp, char *sub, char *rep) {
    char *tmp = mx_strdup(*inp);

    mx_strdel(inp);
    *inp = mx_replace_substr(tmp, sub, rep);
    mx_strdel(&tmp);
}

static void if_tidle(char **inp, char *home, char *pwd) {
    if (mx_isalpha((*inp)[1]))
        tidle_replace(inp, "~", "/Users/");
    else if ((*inp)[1] == '/' || (*inp)[1] == '\0')
        tidle_replace(inp, "~", home);
    else if ((*inp)[1] == '+' && ((*inp)[2] == '/' || (*inp)[2] == '\0'))
        tidle_replace(inp, "~+", pwd);
    else if ((*inp)[1] == '-' && ((*inp)[2] == '/' || (*inp)[2] == '\0')) {
        if (MX_OLDPWD() != NULL)
            tidle_replace(inp, "~-", MX_OLDPWD());
    }
}

void mx_tidle_check(char **input) {
    char *home = mx_strdup("");
    char *pwd = MX_PWD();

    if (getenv("HOME") != NULL) {
        mx_strdel(&home);
        home = MX_HOME();
    }
    if_tidle(input, home, pwd);
    mx_strdel(&home);
    mx_strdel(&pwd);
}
