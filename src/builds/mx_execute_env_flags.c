#include "ush.h"

static int do_command(t_env *env, char **args, int i) {
    int len = 0;

    env->comm_args = mx_strdup(env->comm);
    for (int j = i + 1; args[j] != NULL; j++) {
        len = mx_strlen(env->comm_args) + mx_strlen(args[j]) + 2;
        env->comm_args = realloc(env->comm_args, len);
        mx_strcat(env->comm_args," ");
        mx_strcat(env->comm_args,args[j]);
    }
    return -1;
}

static void flag_P(t_env *env, char *arg) {
    for (int y = 0; env->env_var[y]!= NULL; y++) {
        if (strstr(env->env_var[y], "PATH=") != NULL) {
            mx_strdel(&env->env_var[y]);
            env->env_var[y] = mx_strjoin("PATH=", arg);
            break;
        }
    }
}

static int flag_i(t_env *env, char **args, int i, int *env_in) {
    if (mx_get_char_index(args[i], '=') == 0) {
        fprintf(stderr, "env: setenv %s: Invalid argument\n", args[i]);
        mx_free_env(env);
        return -1;
    }
    if (args[i-1][0] == '-') {
        env->env_var = (char **) malloc(2 * sizeof (char *));
        env->env_var[(*env_in)++] = mx_strdup(args[i]);
        env->env_var[*env_in] = NULL;
    }
    else {
        env->env_var = realloc(env->env_var, (*env_in + 2) * sizeof (char *));
        env->env_var[(*env_in)++] = mx_strdup(args[i]);
        env->env_var[*env_in] = NULL;
    }
    return 0;
}

static int flag_u(t_env *env, char *arg, char **environ) {
    int y = 0;
    char *temp = NULL;

    if (mx_get_char_index(arg, '=') >= 0) {
        fprintf(stderr, "env: unsetenv %s: Invalid argument\n", arg);;
        mx_free_env(env);
        return -1;
    }
    env->env_var = malloc((1) * sizeof (char*));
    temp = mx_strjoin(arg, "=");
    for (int j = 0; environ[j]!= NULL; j++) {
        if(strstr(environ[j], temp) == NULL) {
            env->env_var = realloc(env->env_var,(y + 2) * sizeof (char*));
            env->env_var[y++] = mx_strdup(environ[j]);
        }
    }
    env->env_var[y] = NULL;
    mx_strdel(&temp);
    return 0;
}

int mx_execute_env_flags(t_env *env, char **args, int i, int *env_index) {
    extern char **environ;

    if (env->flag == 2 && args[i-1][0] == '-')
        mx_del_strarr(&env->env_var);
    if (env->comm != NULL && mx_strcmp(args[i],env->comm) != 0)
        return do_command(env, args, i);
    else if (env->flag == 1 && args[i-1][0] == '-'
        && mx_file_exist(args[i]) == 1) {
        flag_P(env, args[i]);
    }
    else if (env->flag == 2 && mx_get_char_index(args[i], '=') >= 0)
        return flag_i(env, args, i, env_index);
    else if (env->flag == 3 && args[i-1][0] == '-')
        return flag_u(env, args[i], environ);
    else if (mx_strcmp(args[i], "./ush") != 0){
        mx_env_error(env, args, i);
        return -1;
    }
    return 0;
}
