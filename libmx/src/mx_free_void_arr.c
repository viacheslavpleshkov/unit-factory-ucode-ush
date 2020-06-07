#include "libmx.h"

void mx_free_void_arr(void **arr, int lines) {
    if (arr != NULL) {
        for (int i = 0; i < lines; i++) {
            free(arr[i]);
            arr[i] = NULL;
        }
        free(arr);
        arr = NULL;
    }
}
