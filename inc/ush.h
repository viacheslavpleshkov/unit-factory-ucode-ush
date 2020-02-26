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

typedef enum e_error {
    ERR_EACCES,
    ERR_DIR,
}            t_error;


typedef struct s_env {
    char *tmpdir;
    char *xpc_flags;
    char *apple_pubsub;
    char *term;
    char *ssh_auth_sock;
    char *seccuritySessionId;
    char *xpc_service_name;
    char *term_program;
    char *term_program_version;
    char *lc_ctype;
    char *term_session_id;
    char *shell;
    char *home;
    char *logname;
    char *user;
    char *path;
    char *shlvl;
    char *pwd; //менять в cd
    char *oldpwd;
    char *homebrew_cache;
    char *homebrew_temp;
}              t_env;

typedef struct s_com {
    char *command;
    char **args;
}              t_com;


//Pwd
void pwd();
//Cd
void cd(char *arr);
#endif
