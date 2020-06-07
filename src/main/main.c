#include "ush.h"

static void executing(t_ush *ush) {
    t_queue **queue = NULL;

    if (ush->command != NULL && strlen(ush->command) > 0) {
        queue = mx_parsing(ush->command);
        ush->return_value = mx_push_execute_queue(queue, ush);
    }
    mx_strdel(&ush->command);
    free(queue);
}

static void sigint () {
    mx_printstr("\n");
}

static void set_shlvl(void) {
    char *shlvl = mx_itoa(mx_atoi(MX_SHLVL()) + 1);

    setenv("SHLVL", shlvl, 1);
    mx_strdel(&shlvl);
}

static void argc_error(int argc, char **argv) {
    if (argc > 1) {
        fprintf(stderr, "ush: can't open input file: %s\n", argv[1]);
        exit(127);
    }
}

int main(int argc, char **argv){
    t_ush *ush = NULL;

    argc_error(argc, argv);
    ush = mx_create_ush(argv);
    set_shlvl();
    while (1) {
        signal(SIGINT, sigint);
        signal(SIGTSTP, SIG_IGN);
        ush->command = mx_process_input(ush);
        executing(ush);
        mx_strdel(&ush->command);
        if (ush->exit_status != -1 || ush->exit_non_term == 1)
            break;
    }
    mx_free_history(ush->history);
    mx_strdel(&ush->ush_path);
    free(ush);
    if (ush->exit_status != -1)
        exit(ush->exit_status);
    return ush->return_value;
}
