#include "ush.h"

void set_canonic(struct termios savetty) {
    tcsetattr (STDIN_FILENO, TCSANOW, &savetty);
}

void mx_set_non_canonic(struct termios *savetty) {
    struct termios tty;
    
    tcgetattr (0, &tty);
    *savetty = tty;
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                     | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_cflag &= ~(CSIZE | PARENB);
    tty.c_cflag |= CS8;
    tty.c_iflag &= IGNCR;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VERASE] = 127;
    tcsetattr (0, TCSAFLUSH, &tty);
}
