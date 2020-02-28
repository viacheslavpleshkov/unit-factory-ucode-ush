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


#define MX_TMPDIR() (getenv("TMPDIR"))
#define MX_XPC_FLAGS() (getenv("XPC_FLAGS"))
#define MX_APPLE_PUBSUB() (getenv("Apple_PubSub_Socket_Render"))
#define MX_TERM() (getenv("TERM"))
#define MX_SSH_AUTH_SOCK() (getenv("SSH_AUTH_SOCK"))
#define MX_SECURITYSESSIONID() (getenv("SECURITYSESSIONID"))
#define MX_XPC_SERVICE_NAME() (getenv("XPC_SERVICE_NAME"))
#define MX_TERM_PROGRAM() (getenv("TERM_PROGRAM"))
#define MX_TERM_PROGRAM_VERSION() (getenv("TERM_PROGRAM_VERSION"))
#define MX_LC_CTYPE() (getenv("LC_CTYPE"))
#define MX_TERM_SESSION_ID() (getenv("TERM_SESSION_ID"))
#define MX_SHELL() (getenv("SHELL"))
#define MX_HOME() (getenv("HOME"))
#define MX_LOGNAME() (getenv("LOGNAME"))
#define MX_USER() (getenv("USER"))
#define MX_PATH() (getenv("PATH"))
#define MX_SHLVL() (getenv("SHLVL"))
#define MX_PWD() (getenv("PWD"))
#define MX_OLDPWD() (getenv("OLDPWD"))
#define MX_HOMEBREW_CACHE() (getenv("HOMEBREW_CACHE"))
#define MX_HOMEBREW_TEMP() (getenv("HOMEBREW_TEMP"))

//Enum
typedef enum e_error {
    ERR_EACCES,
    ERR_DIR,
}            t_error;

typedef enum e_branch {
    RIGHT,
    LEFT
}            t_branch;

//Struct
typedef struct s_env {
    char *key;
    char *value;
    struct s_env *nect;
}              t_env;
typedef struct s_process {
    char **name;
    pid_t pid;
    int index;
}              t_process;
typedef struct s_main {
    char *command;
    t_env *env;
    t_list *history;
    wchar_t emodji_num;
    int exit_status;
}              t_main;

//Main
t_main* mx_create_main();
int main(void);
//Builds function
void pwd(void);
void cd(char **input);
void ls(char **args);
//Input function
char *mx_process_input(int *status);
//Parsing function
//
void mx_print_prompt(wchar_t *emodji_num);
//Validations function
#endif
