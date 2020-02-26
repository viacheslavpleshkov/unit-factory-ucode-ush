#include "libmx.h"

int mx_atoi(const char *str) {
    const int MIN_INTS = -2147483648;
    int sign = 1;
    int num = 0;

    while (mx_isspace(*str)) 
        str++;
    if (*str == '+' || *str == '-') {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (mx_isdigit(*str)) {
        if (sign == -1 && num == 214748364 && *str == 8 + '0')
            return MIN_INTS;
        num *= 10;
        num += *str - '0';
        str++;
    }
    return num * sign;
}
