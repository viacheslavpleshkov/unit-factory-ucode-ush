#include "ush.h"

void mx_insert_char(t_input *input, char sym, int index) {
    char temp;

    input->command = realloc(input->command, mx_strlen(input->command) + 2);
    for (; index < mx_strlen(input->command) + 1; index++) {
        temp = input->command[index];
        input->command[index] = sym;
        sym = temp;
    }
    input->command[index] = '\0';
}


void mx_delete_char(t_input *input, int index) {
    input->command = mx_realloc(input->command, strlen(input->command));
    for (; index < mx_strlen(input->command) - 1; index++) {
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
    str[mx_strlen(str) + 1] = '\0';
    mx_printstr(str);
    mx_strdel(&str);
}
