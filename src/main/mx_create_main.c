#include <ush.h>

t_main* mx_create_main() {
    t_main *main = malloc(sizeof(t_main));

    main->command = NULL;
    main->env = NULL;
    main->history = NULL;
    main->emodji_num = 128512;
    main->exit_status = 1;
    return main;
}
