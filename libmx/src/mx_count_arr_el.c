#include "libmx.h"

int mx_count_arr_el(char **arr) {
    int counter = 0;
    
    if(arr != NULL){
        while (arr[counter]){
            counter++;
        }   
        return counter;
    }
    return 0;
}
