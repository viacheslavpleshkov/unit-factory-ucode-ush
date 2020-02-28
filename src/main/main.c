#include "ush.h"

static void foo(char **input) {
    pid_t pid;
    pid = fork();
    if (pid != 0) {
        if (strcmp(input[0], "cd") == 0)
            cd(input);
        if (strcmp(input[0], "exit") == 0)
            exit(0);
        wait(NULL);
    }
    else {
        if (strcmp(input[0], "pwd") == 0 || strcmp(input[0], "PWD") == 0)
            pwd();
        else if (strcmp(input[0], "ls") == 0 || strcmp(input[0], "LS") == 0)
            ls(input);
        exit(0);
    }
}

static int winsize(void) {
    struct winsize wins;
    int err = ioctl(0, TIOCGWINSZ, &wins);

    if (err == -1)
        return 0;
    return wins.ws_col;
}

static void check_str(char *str, int *status) {
    int win_width = winsize();

    if (mx_strlen(str) + 5 <= win_width) {
        *status = 0;
    }
    else {
        mx_print_error_basic("ush: shell deals only with one line user input\n");
    }
}

static char **parse_input(char *str, int *status) {
    char **input = NULL;

    check_str(str, status);
    if (mx_strchr(str, '\'') != NULL) {
        *status = 2;
        input = mx_strsplit(str, '\'');
        //обработка 'command' , рекурсия ?
    }
    else if (mx_strchr(str, '|') != NULL) {
        *status = 1;
        input = mx_strsplit(str, '|');
        //обработка pipe , рекурсия ?
    }
    else {
        *status = 0;
        input = mx_strsplit(str, ' ');
        //обработка стандартного ввода
    }
    return input;
}


static void executing(int *status, char *str) {
    char **input = NULL;

    if (str != NULL && *status != 3) {
        input = parse_input(str, status);
        foo(input);
        mx_free_void_arr((void **)input, mx_count_arr_el(input));
    }
}

void sigint () {
    //signal(SIGINT, sigint);
    mx_printstr("\n");
}

int main(void) {
    int status = 0;
    //status 0 - normal; 1 - pipe; 2 - commsub; 3 - ^C break;
    t_main *main = mx_create_main();
    while(1) {
        signal(SIGINT, sigint);
        mx_print_prompt(&main->emodji_num);
        main->command = mx_process_input(&status);
        executing(&status, main->command);
        mx_strdel(&main->command);
    }
    return 0;
}
