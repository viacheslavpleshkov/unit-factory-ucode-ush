#include "../inc/libmx.h"

char *mx_strtrim(const char *str){
    int end = mx_strlen(str);
    int start = 0; 
    int a = 0;

    if (str != NULL){
        while(mx_isspace(str[a])){
            start++;
            a++;
        }
        while(mx_isspace(str[end-1])){
            end--;
        }
        char *new_str = mx_strnew(end - start);
        for(int i = start,j=0; i < end; i++){
            new_str[j++] = str[i];
        }
        return new_str;
    }
    return NULL;
}
     

          

