#include "libmx.h"

static int get_len_number(int number) {
    int len = 0;

    for (int i = number; i != 0; i /= 10) 
        len++;
    if (number <= 0)
        len++;

    return len;
}

char *mx_itoa(int number) {
    int len = 0;
    int sign = 1;
    char *mitoa = NULL; 

    len = get_len_number(number);
    mitoa = mx_strnew(len);   
    if (number == 0)
        mitoa[0] = '0';
    else {
        if (number < 0) 
            sign = -1;
        for (int i = len - 1; i >= 0; i--) {
            mitoa[i] = (number % 10) * sign + '0';
            number /= 10;
        }
        if (sign == -1) 
            mitoa[0] = '-';
    }
    mitoa[len] = '\0';
    return mitoa;
}
