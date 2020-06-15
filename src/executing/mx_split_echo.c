#include "ush.h"

static void insert_chars(char **str, char sym, int index) {
    char temp;
    int len = mx_strlen(*str);

    (*str) = realloc((*str), len + 2);
    for (; index < len + 1; index++) {
        temp = (*str)[index];
        (*str)[index] = sym;
        sym = temp;
    }
    (*str)[index] = '\0';
}

static char **insertin_arr(char c, char *str_input) {
    char **arr = NULL;

    arr = mx_strsplit(str_input, c);
    insert_chars(&(arr[1]), c, 0);
    insert_chars(&(arr[1]), c, mx_strlen(arr[1]));
    return arr;
}

char **mx_split_echo(char *str_input, int check) {
    char **arr = NULL;
    char **e_f = NULL;
    int arr_el = 0;

    if (check == 2)
        arr = insertin_arr('\'', str_input);
    else
        arr = insertin_arr('\"', str_input);
    e_f = mx_strsplit(arr[0], ' ');
    arr_el = mx_count_arr_el(e_f);
    for (int i = 1; arr[i] != NULL; i++) {
        e_f = (char **) realloc(e_f, sizeof(char *) * (arr_el + 2));
        e_f[arr_el++] = mx_strdup(arr[i]);
        e_f[arr_el] = NULL;
    }
    mx_free_void_arr((void **)arr, mx_count_arr_el(arr));
    return e_f;
}

int mx_check_echo(char **n) {
    int flag_one = 0;
    int flag_two = 0;

    if (mx_strcmp(n[0], "echo") == 0 || mx_strcmp(n[0], "/bin/echo") == 0) {
        for (int i = 0; i < mx_count_arr_el(n); i++) {
            if (n[i][0] == '-')
                continue;
            else if (n[i][0] == '$')
                return 0;
            else if (n[i][0] == '\'' || n[i][mx_strlen(n[i]) - 1] == '\'')
                flag_one++;
            else if (n[i][0] == '\"' || n[i][mx_strlen(n[i]) - 1] == '\"')
                flag_two++;
        }
    }
    if (flag_one == 2 && flag_two == 0)
        return 2;
    else if (flag_one == 0 && flag_two == 2)
        return -2;
    return 0;
}
