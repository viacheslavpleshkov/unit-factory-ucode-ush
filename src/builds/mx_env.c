#include "ush.h"

static t_env *create_env(void) {
    t_env *env = (t_env *) malloc(sizeof (t_env));
    int i = 0;
    extern char **environ;
    int size = mx_count_arr_el(environ) + 1;

    env->flag = 0;
    env->comm = NULL;
    env->env_var = NULL;
    env->comm_args = NULL;
    env->env_var = (char **) malloc(size * sizeof (char *));
    for (int j = 0; environ[j] != NULL; j++)
        env->env_var[i++] = mx_strdup(environ[j]);
    env->env_var[i] = NULL;
    return env;
}

static int check_flag(char **args, int i, t_env *env) {//
    if (mx_strcmp(args[i], "--") == 0) {
        env->flag = 4;
        return 0;
    }
    else if (args[i][0] == '-' && env->flag != 4) {
        if (mx_find_flag("Piu", args[i]) == 0) {
            fprintf(stderr, MX_ENV_IL, args[i][1]);
            mx_free_env(env);
            return -1;
        }
        else if (mx_find_flag("Piu", args[i]) < 3
            && env->flag == 0 && args[i + 1] == NULL) {
            fprintf(stderr, MX_ENV_US, args[i][1]);
            mx_free_env(env);
            return -1;//break
        }
        else if (mx_find_flag("Piu", args[i]) > env->flag)
            env->flag = mx_find_flag("Piu", args[i]);
        return 0;
    }
    return 1;
}

static void create_command(t_env *env, char *arg) {
    int y = 0;

    for (; env->env_var[y]!= NULL; y++) {
        if (strstr(env->env_var[y], "PATH=") != NULL)
            break;
    }
    if (env->env_var[y] == NULL)
        env->comm = mx_coomand_in_path(arg, MX_PATH());
    else
        env->comm = mx_coomand_in_path(arg, env->env_var[y]);
}

static t_env *parse_env_args(char **args) {
    t_env *env = create_env();
    int len = mx_count_arr_el(args);
    int env_index = 0;

    for (int i = 1; i < len; i++) {
        if (check_flag(args, i, env) == -1)
            break;
        else if (check_flag(args, i, env) == 0)
            continue;
        create_command(env, args[i]);
        if (mx_execute_env_flags(env, args, i, &env_index) == -1)
            break;
        if (env != NULL)
            mx_strdel(&env->comm);
    }
    if (env == NULL)
        return NULL;
    return env;
}

int mx_env(char **args, t_ush *ush) {
    t_env *env = parse_env_args(args);
    int ret_val = 0;
    char **env_args = NULL;

    if (env != NULL) {
        if (env->comm == NULL || mx_strcmp(env->comm, "env") == 0)
            mx_print_strarr(env->env_var, "\n");
        else if (env->comm != NULL && ush != NULL) {
            env_args = mx_strsplit(env->comm_args, ' ');
            if (fork())
                wait(NULL);
            else if (env->env_var != NULL){
                if (execve(env_args[0], env_args, env->env_var) == -1)
                    perror("execve");
                exit(1);
            }
            mx_free_void_arr((void**)env_args, mx_count_arr_el(env_args));
        }
        return ret_val;
    }
    return 1;
}

