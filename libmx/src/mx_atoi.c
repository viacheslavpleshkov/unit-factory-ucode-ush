#include "libmx.h"

int mx_atoi(const char *str) {
    const int MIN_INTS = -2147483648;
    int sign = 1;
    int num = 0;
    int i = 0;

    while (mx_isspace(str[i]))
        i++;
    if (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (mx_isdigit(str[i])) {
        if (sign == -1 && num == 214748364 && str[i] == 8 + '0')
            return MIN_INTS;
        num *= 10;
        num += str[i] - '0';
        i++;
    }
    return num * sign;
}
