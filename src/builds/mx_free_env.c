#include "ush.h"

void mx_free_env(t_env *env) {
    if (env != NULL) {
        mx_free_void_arr((void**)env->env_var, mx_count_arr_el(env->env_var));
        mx_strdel(&env->comm_args);
        mx_strdel(&env->comm);
        free(env);
        //env = NULL;
    }
}
