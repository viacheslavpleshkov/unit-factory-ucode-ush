#include "ush.h"

void mx_com_sub_free(t_com_sub *com_sub) {
    if (com_sub != NULL) {
        mx_strdel(&com_sub->temp_join);
        mx_strdel(&com_sub->temp_str);
        mx_strdel(&com_sub->cout_execute);
    }
}
