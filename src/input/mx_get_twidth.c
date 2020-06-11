#include "ush.h"

int mx_get_twidth(void) {
    struct winsize wins;
    int err = ioctl(0, TIOCGWINSZ, &wins);//заменить запрет функция
    if (err == -1)
        return 0;
    return wins.ws_col;

//    if (tgetent(NULL, "xterm-256color") < 0) {
//        fprintf(stderr, "ush: Could not access the termcap data base.\n");
//        exit(1);
//    }
//    return tgetnum("co");
}
