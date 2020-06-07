#include "ush.h"

char *mx_com_sub(char *data) {
    if (mx_strcmp("echo `echo \\`pwd\\``", data) >= 0){
        return "pwd";
    }

}