#include "libmx.h"

char *mx_strtrim(const char *str){
    int end = mx_strlen(str);
    int start = 0; 
    int a = 0;
    char *new_str = NULL;

    if (str != NULL){
        while(mx_isspace(str[a])) {
            start++;
            a++;
        }
        while(mx_isspace(str[end-1]))
            end--;
        new_str = mx_strnew(end - start);
        for(int i = start,j=0; i < end; i++)
            new_str[j++] = str[i];
        return new_str;
    }
    return NULL;
}
     

          

