#include "ush.h"


static void uls(char **args) {
    int args_elem = mx_count_arr_el(args);
    char ** arr = malloc(sizeof(char*) * (args_elem + 1));
    arr[0] = mx_strdup( "/bin/ls");
    for (int  i = 1; i < args_elem; i++) {
        arr[i] = mx_strdup(args[i]);
    }
    arr[args_elem] = NULL;
    execv("/bin/ls",arr);
    mx_free_void_arr((void**)arr, args_elem);
}

static void foo(char **input) {
    pid_t pid;
    pid = fork();
    if (pid != 0) {
        if (strcmp(input[0], "cd") == 0)
            cd(input[1]);
        if (strcmp(input[0], "exit") == 0)
            exit(0);
        wait(NULL);
    }
    else {
        if (strcmp(input[0], "pwd") == 0 || strcmp(input[0], "PWD") == 0)
            pwd();
        else if (strcmp(input[0], "ls") == 0 || strcmp(input[0], "LS") == 0)
            uls(input);
        exit(0);
    }
    //mx_free_void_arr((void**)input, mx_count_arr_el(input));
}

static void set_non_canonic(struct termios *savetty) {
    struct termios tty;

    if ( !isatty(0) ) {
        fprintf (stderr, "stdin not terminal\n");
        exit (1);
    }
    tcgetattr (0, &tty);
    *savetty = tty;
    tty.c_lflag &= ~(ICANON|ISIG|ECHO);
    tty.c_cc[VMIN] = 1;
    tcsetattr (0, TCSAFLUSH, &tty);
}

static void set_canonic(struct termios savetty) {
    tcsetattr (STDIN_FILENO, TCSANOW, &savetty);
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

static char *read_str(char *str, int *status) {
    char ch;
    int i = 0;

    while(1) {
        read(0, &ch, 1);
        if  (ch == 4) {
            mx_printchar('\n');
            exit(0);
        }
        else if  (ch == 3) {
            *status = 3;
            mx_printchar('\n');
            break;
        }
        else {
            mx_printchar(ch);
            if(ch != '\n') {
                str = mx_realloc(str, sizeof(char) * (i + 2));
                str[i] = ch;
                i++;
            }
            else
                break;
        }
    }
    if (str != NULL)
        str[i] = '\0';
    return str;
}

static char *process_str(int *status) {// сделать обработку \ и enter перенос строки продолжение ввода
    // обработка в другом процессе () subshell
    char *str = NULL;
    struct termios savetty;

    set_non_canonic(&savetty);
    str = read_str(str, status);
    set_canonic(savetty);
    return str;
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

int main() {
    char *str = NULL;
    int status = 0;
    //status 0 - normal; 1 - pipe; 2 - commsub; 3 - ^C break;

    while(1) {
        signal(SIGINT, sigint);
        mx_print_unicode(128520);
        mx_printstr("\033[0;35m");
        mx_printstr(" u$h> ");
        mx_printstr("\33[0m");
        str = process_str(&status);
        executing(&status, str);
        mx_strdel(&str);

    }
    return 0;
}
