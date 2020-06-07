#include "ush.h"
static mx_free_com_sub()

char *mx_strindup(const char *data, int first,int end) {
    int len = 0;

    if (!data)
        return NULL;
    len = mx_strlen(data);

    return mx_strncpy(mx_strnew(end - first), data, end);
}

char *mx_com_sub_validation(char *data) {
    t_com_sub *com_sub = mx_create_com_sub();
    char *temp_str = NULL;
    char *temp_execute = NULL;
    char *cout_execute = NULL;
    int status = 0;

    for (int i = 0; data[i] != '\0'; i++) {
        if(data[i] == '`') {
            if (com_sub->space == 0) {
                com_sub->space++;
                com_sub->space_first_index = i;
            } else if (com_sub->space == 1)
                com_sub->space++;
                com_sub->space_end_index = i;
                if (space_first_index < space_end_index) {
                    temp_str = mx_strindup(data, space_first_index, space_end_index);
                    status = mx_execute(ush, temp_str, 0, cout_execute);
                    mx_replace_substr(data, temp_execute, cout_execute);
                }
            }
        }
        if (data[i] == '$(' && com_sub->space_first_index == 0) {
            com_sub->space_first_index = i;
            com_sub->space_first++;
        }
        if (data[i] == '$(' && com_sub->space_first_index !)
    }
}