#include "ush.h"

static void executing(t_ush *ush) {
    t_queue **queue = NULL;

    if (ush->command != NULL && strlen(ush->command) > 0) {
        queue = mx_parsing(ush->command);
        ush->return_value = mx_push_execute_queue(queue, ush);
    }
    mx_strdel(&ush->command);
    if (queue != NULL)
        free(queue);
}

static void sigint () {
    mx_printstr("\n");
}

static void argc_error(int argc, char **argv) {
    if (argc > 1) {
        fprintf(stderr, "ush: can't open input file: %s\n", argv[1]);
        exit(127);
    }
}
static void free_pids(t_pid *pids) {
    t_pid *temp = NULL;

    if(pids != NULL) {
        while (pids->prev != NULL) {
            temp = pids;
            pids = pids->prev;
            mx_strdel(&temp->str);
            free(temp);
        }
        mx_strdel(&pids->str);
        free(pids);
    }
}

int main(int argc, char **argv){
    t_ush *ush = NULL;

    argc_error(argc, argv);
    ush = mx_create_ush(argv);
    mx_set_shl();
    while (1) {
        signal(SIGINT, sigint);
        signal(SIGTSTP, SIG_IGN);
        ush->command =  mx_process_input(ush);
        executing(ush);
        if (ush->exit_status != -1 || ush->exit_non_term == 1)
            break;
    }
    mx_free_history(ush->history);
    mx_strdel(&ush->ush_path);
    free_pids(ush->pids);
    free(ush);
    if (ush->exit_status != -1)
        exit(ush->exit_status);
    return ush->return_value;
}
