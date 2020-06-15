#include "ush.h"

void mx_free_env(t_env *env) {
    if (env != NULL) {
        mx_del_strarr(&env->env_var);
        mx_strdel(&env->comm_args);
        mx_strdel(&env->comm);
        free(env);
    }
}
