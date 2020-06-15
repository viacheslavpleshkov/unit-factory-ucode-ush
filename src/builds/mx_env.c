#include "ush.h"

int mx_env(char **args, t_ush *ush) {
    t_env *env = mx_parse_env_args(args);
    char **env_args = NULL;

    if (env != NULL) {
        if (env->comm == NULL || mx_strcmp(env->comm, "env") == 0)
            mx_print_strarr(env->env_var, "\n");
        else if (env->comm != NULL && ush != NULL) {
            env_args = mx_strsplit(env->comm_args, ' ');
            if (fork())
                wait(NULL);
            else {
                execve(env_args[0], env_args, env->env_var);
                exit(1);
            }
            mx_free_void_arr((void **)env_args, mx_count_arr_el(env_args));
        }
        mx_free_env(env);
        return 0;
    }
    return 1;
}

