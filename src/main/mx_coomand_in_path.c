#include "ush.h"

static char *check_in_path(char *command, char **path) {
    char *command_p = NULL;

    for (int i = 0; i < mx_count_arr_el(path); i++) {
        command_p = mx_strnew(mx_strlen(command) + mx_strlen(path[i]) + 1);
        mx_strcpy(command_p, path[i]);
        command_p = mx_strcat(command_p, "/");
        command_p = mx_strcat(command_p, command);
        if (mx_file_exist(command_p))
            break;
        mx_strdel(&command_p);
    }
    return command_p;
}

char *mx_coomand_in_path(char *comm, char *str_path) {
    char **path = NULL;
    char *command_p = NULL;
    int paths = 0;
    int i = 0;

    if (str_path != NULL) {
        path = mx_strsplit(str_path, ':');
        paths = mx_count_arr_el(path);
        if (strstr(str_path, "PATH=") != NULL) {
            for (; i < mx_strlen(path[0]) - 5; i++)
                path[0][i] = path[0][i + 5];
            path[0][i] = '\0';
        }
        if (mx_strcmp(comm, "/") != 0 && mx_get_char_index(comm, '/') == -1)
            command_p = check_in_path(comm, path);
        mx_free_void_arr((void **) path, paths);
    }
    if (command_p == NULL)
        command_p = mx_strdup(comm);
    return command_p;
}
