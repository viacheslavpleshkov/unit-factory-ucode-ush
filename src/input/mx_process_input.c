#include "ush.h"

static t_input *init_input() {
    t_input *input = (t_input *) malloc(sizeof (t_input));

    input->len = 0;
    input->command = mx_strnew(1);//?
    input->ctrl_c = 0;
    input->coursor_position = 0;
    input->input_ch = '\0';
    input->input_ch_arr = (char *)&input->input_ch;
    return input;
}


static char *inside_cycle(t_input *input, int *flag, t_ush *ush, char *str) {
    int k = 0;
    int i = mx_getch(input);

    while (k < i) {
        input->input_ch = input->input_ch_arr[k];
        if (input->input_ch <= 127 && input->input_ch != 27) {
            str = mx_input_ascii(input, ush);
            if (ush->exit_status != -1)
                break;
        }
        else {
            *flag = 0;
            mx_input_non_ascii(input, ush);
        }
        if (input->input_ch < 32)
            break;
        k++;
    }
    return str;
}


static char *read_str(struct termios savetty, t_ush *ush) {
    char *ret_str = NULL;
    char *temp = NULL;
    int flag = 0;
    t_input *input = init_input();

    input->savetty = savetty;
    input->term_width = mx_get_twidth();
    while (input->input_ch != '\r' && input->ctrl_c != 1
            && input->term_width != 0) {
        ret_str = inside_cycle(input, &flag, ush, ret_str);
        if (ush->exit_status != -1)
            break;
        if (input->len > 0)
            temp = mx_add_history(input, &flag, ush, temp);
    }
    if (ush->history->next != NULL)
        mx_sort_history(ush, temp);
    mx_free_step(input, temp);
    mx_printstr("\n");
    return ret_str;
}

char *mx_process_input(t_ush *ush) {
    char *str = NULL;
    struct termios savetty;
    size_t bufsize = 32;
    char *buffer = NULL;

    if (!isatty(0)) {
        getline(&buffer,&bufsize,stdin);
        str = mx_strndup(buffer, mx_strlen(buffer) - 1);
        ush->exit_non_term = 1;
        mx_strdel(&buffer);
    }
    else {
        mx_print_prompt(1, ush);
        mx_set_non_canonic(&savetty);
        str = read_str(savetty, ush);
        set_canonic(savetty);
    }
    if (ush->history->data != NULL)
        ush->history = mx_addelem(ush->history);
    return str;
}
