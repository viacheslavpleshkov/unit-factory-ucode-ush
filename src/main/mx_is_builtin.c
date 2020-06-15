#include "ush.h"

static int is_built(char *command) {
    if (strcmp("cd", command) == 0)
        return 1;
    if (strcmp("pwd", command) == 0)
        return 2;
    if (strcmp("echo", command) == 0)
        return 9;
    return 0;
}

int mx_is_builtin(char *command) {
    int num = 0;
    char builtins[][20] = {"/usr/bin/cd", "/bin/pwd", "/usr/bin/env",
                           "ush", "export", "unset", "exit",
                           "/usr/bin/which", "/bin/echo"};

    for (int i = 0; i < mx_strlen(command); i++)
        command[i] = (char)mx_tolower(command[i]);
    if ((num = is_built(command)) == 0) {
        for (int i = 0; i < 10; i++) {
            if (strcmp(builtins[i], command) == 0) {
                num = i + 1;
            }
        }
    }
    return num;
}
