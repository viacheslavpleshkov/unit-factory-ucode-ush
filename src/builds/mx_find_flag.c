#include "ush.h"

int mx_find_flag(char *flags, char *arg) {
    int flag = 0;

    for (int i = 0; i < (int)strlen(flags); i++) {
        for (int y = 1; y < (int)strlen(arg); y++) {
            if (arg[y] == flags[i]) {
                if (i + 1 > flag)
                    flag = i + 1;
                break;
            }
        }
    }
    return flag;
}
