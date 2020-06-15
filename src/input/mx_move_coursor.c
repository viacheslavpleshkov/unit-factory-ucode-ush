#include "ush.h"

void mx_insert_char(t_input *input, char sym, int index) {
    char temp;
    int len = mx_strlen(input->command);

    input->command = realloc(input->command, len + 2);
    for (; index < len + 1; index++) {
        temp = input->command[index];
        input->command[index] = sym;
        sym = temp;
    }
    input->command[index] = '\0';
}


void mx_delete_char(t_input *input, int index) {
    int len =  mx_strlen(input->command);

    input->command = realloc(input->command, len);
    for (; index < len - 1; index++) {
        input->command[index] = input->command[index + 1];
    }
    input->command[index] = '\0';
}

void mx_move_coursor(int num_of_moves, char *side) {
    char *str2 = "\033[";
    char *str1 = mx_itoa(num_of_moves);
    char *temp = mx_strjoin(str1,side);
    char *str = mx_strjoin(str2,temp);

    mx_strdel(&str1);
    mx_strdel(&temp);
    mx_printstr(str);
    mx_strdel(&str);
}
