#include "ush.h"

void mx_print_prompt(int flag, t_ush *ush) {
    if (flag == 1) {
        srandom(time(NULL));
        ush->emodji_num = random() % 79 + 128512;
    }
    mx_print_unicode(ush->emodji_num);
    mx_printstr("\033[0;32;1m");
    mx_printstr("u$h");
    mx_printstr("\033[0;31;1m");
    mx_printstr("> ");
    mx_printstr("\33[0m");
}
