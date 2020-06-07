#include "ush.h"

void mx_env_error(t_env *env, char **args, int i) {
    if (mx_file_exist(args[i]) != 1)
        fprintf(stderr, "env: %s: No such file or directory\n", args[i]);
    else if (mx_file_exist(args[i]) == 1)
        fprintf(stderr, "env: %s: Permission denied\n", args[i]);
    mx_free_env(env);
}
