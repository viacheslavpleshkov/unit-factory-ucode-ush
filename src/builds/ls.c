#include "ush.h"

void ls(char **args) {
    int args_elem = mx_count_arr_el(args);
    char ** arr = malloc(sizeof(char*) * (args_elem + 1));
    arr[0] = mx_strdup( "/bin/ls");
    for (int  i = 1; i < args_elem; i++) {
        arr[i] = mx_strdup(args[i]);
    }
    arr[args_elem] = NULL;
    execv("/bin/ls",arr);
    mx_free_void_arr((void**)arr, args_elem);
}
