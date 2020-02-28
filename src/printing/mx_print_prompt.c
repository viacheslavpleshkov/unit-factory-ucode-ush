#include "ush.h"

void mx_print_prompt(wchar_t *emodji_num) {
    mx_print_unicode((*emodji_num)++);
        if (*emodji_num == 128591)
            *emodji_num = 128512;
        mx_printstr("\033[0;32;1m");
        mx_printstr("u$h> ");
        mx_printstr("\33[0m");
}
