#include "ush.h"

t_queue **mx_parsing(char *command) {
    char **arr = mx_strsplit(command, ';');
    int size = mx_count_arr_el(arr);
    t_queue **arr_queue = (t_queue **)malloc(sizeof(t_queue *) * (size + 1));

    for (int i = 0; i < size; i++) {
        arr_queue[i] = NULL;
        mx_insort_t_queue(arr[i], &arr_queue[i]);
    }
    mx_free_void_arr((void **)arr, size);
    arr_queue[size] = NULL;
    return arr_queue;
}
