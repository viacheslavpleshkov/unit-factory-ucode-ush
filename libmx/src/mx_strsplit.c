#include "libmx.h"

char **mx_strsplit(const char *s, char c) {
    int i = 0;
    int begin = 0;
    int size = mx_count_words(s, c);
    char *tmp = mx_strtrim_char(s, c);
    char **result = (char**) malloc(sizeof(char*) * (size + 1));

    if (tmp)
        for (int k = 0; k < size; k++) {
            while (tmp[i] && tmp[i] == c) 
                i++;
            begin = i;  
            while (tmp[i] && tmp[i] != c) 
                i++;   
            result[k] = mx_strndup(&tmp[begin], i - begin);
        }
    result[size] = NULL;
    mx_strdel(&tmp);
    return result;
}
