#include <ush.h>

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

static char *read_str(char *str) {
//    str = malloc(sizeof (char) * CHAR_MAX/8);
//    size_t bufsize = CHAR_MAX/8;
//    getline(&str, &bufsize, stdin);
//    mx_printstr(str);
    char ch;
    int i = 0;

    while(1) {
        read(0, &ch, 1);
        if  (ch == 4) {
            mx_printchar('\n');
            exit(0);
        }
        else if  (ch == 3) {
           // *status = 3;
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

char *mx_process_input(int *status) {// сделать обработку \ и enter перенос строки продолжение ввода
    // обработка в другом процессе () subshell
    char *str = NULL;
    status++;
    struct termios savetty;

    set_non_canonic(&savetty);
    str = read_str(str);
    set_canonic(savetty);
    return str;
}
