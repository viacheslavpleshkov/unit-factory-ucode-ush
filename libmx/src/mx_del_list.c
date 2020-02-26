#include "libmx.h"

void mx_del_list(t_list *list, int leng) {
    for (int i = 0; i < leng; i++)
        mx_pop_back(&list);
}
