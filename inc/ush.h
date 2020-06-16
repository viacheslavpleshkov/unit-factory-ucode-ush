#ifndef USH_H
#define USH_H

#include "libmx.h"
#include <limits.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <termcap.h>
#include <time.h>
#include <pwd.h>

#define MX_HOME() (mx_getenv("HOME"))
#define MX_PATH() (mx_getenv("PATH"))
#define MX_SHLVL() (mx_getenv("SHLVL"))
#define MX_PWD() (mx_getenv("PWD"))
#define MX_OLDPWD() (mx_getenv("OLDPWD"))

#define MX_RIGHT_ARROW 67
#define MX_LEFT_ARROW 68
#define MX_UP_ARROW 65
#define MX_DOWN_ARROW 66
#define MX_ENTER 13
#define MX_BACKSPACE 127
#define MX_TAB 9

#define MX_ENV_US "env: option requires an argument -- %c\nusage: env [-i] \
[-P utilpath] [-u name]\n           \
[name=value ...] [utility [argument ...]]\n"
#define MX_ENV_IL "env: illegal option -- %c\nusage: env [-iv] [-P utilpath] \
[-u name]\n           [name=value ...] [utility [argument ...]]\n"
#define MX_PWD_ERR "ush: pwd: -%c: invalid option\npwd: usage: pwd [-LP]\n"
#define MX_WHICH_US "which: illegal option -- \
%c\nusage: which [-as] program ...\n"

//Struct
typedef struct s_queue t_queue;
typedef struct s_input t_input;
typedef struct s_ush t_ush;
typedef struct s_redirect t_redirect;
typedef struct s_env t_env;
typedef struct s_dbl_list t_dbl_list;
typedef struct s_pid t_pid;
typedef struct s_com_sub t_com_sub;

struct s_com_sub {
    int back_first;
    int back_first_index;
    int back_end;
    int back_end_index;
    int space;
    int space_first_index;
    int space_end_index;
    char *temp_str;
    char *temp_data;
    char *cout_execute;
    char *temp_join;
    int status;
};

struct s_queue {
    char *data;
    char operator;
    struct s_queue *next;
};

struct s_input {
    int ctrl_c;
    unsigned char input_ch;
    char *input_ch_arr;
    int len;
    int term_width;
    int coursor_position;
    char *command;
    struct termios savetty;
};

struct  s_env {
    int flag;
    char *comm;
    char *comm_args;
    char **env_var;
};

struct s_dbl_list {
    t_dbl_list *next;
    t_dbl_list *prev;
    char *data;
};

struct s_ush {
    char *command;
    t_dbl_list *history;
    wchar_t emodji_num;
    char *ush_path;
    int return_value;
    int exit_status;
    t_pid *pids;
    char *str_input;
    int exit_non_term;
    int curr_pid;
    char *pwd_l;
    char *pwd;
};

struct s_pid {
    int num;
    int index;
    char *str;
    struct s_pid *next;
    struct s_pid *prev;
};
struct s_redirect {
    int fd_return[2];
    int fd_stdout[2];
    int fd_stderr[2];
    int flag;
    char *_stdout;
    char *_stderr;
};

//Main function
t_ush* mx_create_ush(char **argv);
int mx_is_builtin(char *command);
void mx_write_to_pipe(char *str, int *fd);
void mx_read_from_pipe(char *str, int len, int *fd);
char *mx_coomand_in_path(char *command, char *str_path);
void mx_set_shl(void);

//Builds function
int mx_pwd(char **args, t_ush *ush);
int mx_cd(char **args, t_ush *ush);
int mx_env(char **args, t_ush *ush);
int mx_export(char **args);
int mx_unset(char **args);
int mx_exit(char **inp, int *exit_status);
int mx_echo(char **args);
int mx_which(char **input);

int mx_find_flag(char *flags, char *arg);
int mx_file_exist(char *path);
int mx_check_symlink(char **arg, int flag, int link);
char *mx_parse_echo(char **args, int *flag_n);
int mx_execute_env_flags(t_env *env, char **args, int i, int *env_index);
void mx_free_env(t_env *env);
void mx_env_error(t_env *env, char **args, int i);
char *mx_getenv(char *var);
t_env *mx_parse_env_args(char **args, t_ush *ush);
int mx_make_path(char *path, t_ush *ush, int flag);
void mx_setenv_ush(char *arg, t_ush *ush);

//Executing function
int mx_execute(t_ush *ush, char *str_input, int flag_redir, char **str_red);
int mx_push_execute_queue(t_queue **queue, t_ush *ush);
char **mx_check_expansion(char *str_input, int ret_val);
t_redirect *mx_create_redirect(int flag_redir);
void mx_parent_redirect(t_redirect *redirect, int *return_);
void mx_child_redirect(t_redirect *redirect);
void mx_child_execute(int *ret, char **inp, t_redirect *red, t_ush *ush);
void mx_free_execute(t_redirect *redirect, char **input);
int mx_check_echo(char **n);
char **mx_split_echo(char *str_input, int check);
void mx_tidle_check(char **input);

//Input function
void mx_clear_str();
char *mx_input_ascii(t_input *input, t_ush *ush);
char *mx_fill_command(t_input *input, t_ush *ush);
void mx_input_non_ascii(t_input *input, t_ush *ush);
char *mx_process_input(t_ush *ush);
void mx_set_non_canonic(struct termios *savetty);
void set_canonic(struct termios savetty);
int mx_get_twidth(void);
int mx_getch(t_input *input);
char *mx_add_history(t_input *input, int *flag, t_ush *ush, char *temp);
void mx_sort_history(t_ush *ush, char *temp);
void mx_free_step(t_input *input, char *temp);
t_dbl_list *mx_addelem(t_dbl_list *history);
void mx_move_coursor(int num_of_moves, char *side);
void mx_insert_char(t_input *input, char sym, int index);
void mx_delete_char(t_input *input, int index);

//Parsing function
t_queue **mx_parsing(char *command);
int mx_count_queue_operation(const char *arr);
t_queue *mx_create_queue(char *data, char operation);
void mx_pop_front_queue(t_queue **head);
void mx_push_back_queue(t_queue **queue, char *data, char operation);
void mx_insort_t_queue(char *arr, t_queue **arr_queue);

//Printing function
void mx_print_prompt(int flag, t_ush *ush);

//Utils function
char **mx_util_strsplit_one(const char *s, char *c);
char *mx_util_replace_operator(char *s);
int mx_util_get_flag_index(const char *str, const char *sub);
char *mx_util_strincpy(char *dst, const char *src, int first, int end);
char *mx_util_strindup(const char *data, int first, int end);

//Com sub
t_com_sub* mx_create_com_sub();
int mx_com_sub_space(char **data, t_com_sub *c, t_ush *ush, int i);
int mx_com_sub_back(char **data, t_com_sub *c, t_ush *ush, int i);
void mx_com_sub(char **data, t_ush *ush);
void mx_com_sub_free(t_com_sub *com_sub);

//History
void mx_free_ush(t_ush *ush);
#endif
