#include "ush.h"

static char *homedir() {
    struct passwd *pw = getpwuid(getuid());

    if (getenv("HOME") == NULL)
        return mx_strdup(pw->pw_dir);

    return mx_strdup(getenv("HOME"));
}

char *mx_getenv(char *var) {
    if (strcmp(var, "PWD") == 0)
        return getcwd(NULL, 0);
    if (strcmp(var, "HOME") == 0)
        return homedir();
    if (strcmp(var, "SHLVL") == 0) {
        if (getenv("SHLVL") == NULL)
            return mx_strdup("1");
        return mx_strdup(getenv("SHLVL"));
    }
    if (strcmp(var, "OLDPWD") == 0) {
        if (getenv("OLDPWD") == NULL)
            return NULL;
        return getenv("OLDPWD");
    }
    if (strcmp(var, "PATH") == 0) {
        if (getenv("PATH") == NULL)
            return "/bin:/usr/bin:/usr/ucb:/usr/local/bin";
        return getenv("PATH");
    }
    return NULL;
}
