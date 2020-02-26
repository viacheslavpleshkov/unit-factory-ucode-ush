#include "ush.h"

void cd(char *arr) {
    if(arr != NULL)
        chdir(arr);
    else
        chdir(MX_PWD());
}
