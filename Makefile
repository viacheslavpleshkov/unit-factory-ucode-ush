APP_NAME = ush

LIBMXF = libmx

LIB_NAME = libmx.a

INC = \
inc/ \
libmx/inc/

SRC_DIR = src

OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/,\
	builds/mx_cd.c \
	builds/mx_pwd.c \
	builds/mx_env.c \
	builds/mx_export.c \
	builds/mx_exit.c \
	builds/mx_echo.c \
	builds/mx_which.c \
	builds/mx_ush.c\
	builds/mx_check_symlink.c\
	builds/mx_find_flag.c\
	builds/mx_file_exist.c\
	builds/mx_parse_cd_args.c\
	builds/mx_parse_echo.c\
	builds/mx_execute_env_flags.c\
	builds/mx_free_env.c\
	builds/mx_env_error.c\
	input/mx_process_input.c \
	input/mx_input_ascii.c \
	input/mx_input_non_ascii.c \
	input/mx_set_non_canonic.c \
	input/mx_fill_command.c \
	input/mx_get_twidth.c \
	input/mx_getch.c \
	input/mx_move_coursor.c \
    parsing/mx_count_queue_operation.c \
    parsing/mx_create_queue.c \
    parsing/mx_insort_t_queue.c \
    parsing/mx_parsing.c \
    parsing/mx_pop_front_queue.c \
    parsing/mx_push_back_queue.c \
	printing/mx_print_prompt.c \
	executing/mx_execute.c \
	executing/mx_push_execute_queue.c \
	executing/mx_check_expansion.c \
	executing/mx_create_redirect.c\
	executing/mx_child_execute.c\
	main/mx_coomand_in_path.c \
	main/mx_create_ush.c \
	main/mx_is_builtin.c \
	main/mx_use_pipe.c \
	main/main.c \
	history/mx_free_history.c \
	utils/mx_util_get_flag_index.c \
    utils/mx_util_replace_operator.c \
    utils/mx_util_strsplit_one.c)

OBJ = \
	mx_cd.o \
    mx_pwd.o \
    mx_env.o \
    mx_export.o \
    mx_exit.o \
    mx_echo.o \
    mx_which.o \
    mx_ush.o \
    mx_parse_cd_args.o\
    mx_check_symlink.o\
    mx_find_flag.o\
    mx_parse_echo.o\
    mx_execute_env_flags.o\
    mx_env_error.o\
    mx_free_env.o\
    mx_file_exist.o\
    mx_process_input.o \
    mx_input_ascii.o \
    mx_input_non_ascii.o \
    mx_set_non_canonic.o \
    mx_fill_command.o \
    mx_get_twidth.o \
    mx_getch.o \
    mx_move_coursor.o \
    mx_count_queue_operation.o \
    mx_create_queue.o \
    mx_insort_t_queue.o \
    mx_parsing.o \
    mx_pop_front_queue.o \
    mx_push_back_queue.o \
    mx_print_prompt.o \
    mx_execute.o \
    mx_push_execute_queue.o \
    mx_check_expansion.o \
    mx_create_redirect.o \
    mx_child_execute.o \
    mx_coomand_in_path.o \
    mx_create_ush.o \
    mx_is_builtin.o \
    mx_use_pipe.o \
    main.o \
    mx_free_history.o \
    mx_util_get_flag_index.o \
    mx_util_replace_operator.o \
    mx_util_strsplit_one.o
CC = clang

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all : install

install : libmx/libmx.a uls

libmx/libmx.a:
	@make -C $(LIBMXF)

uls : $(SRC) inc/ush.h libmx/libmx.a
	@$(CC) $(CFLAGS) -c $(SRC) $(foreach d, $(INC), -I $d)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBMXF)/$(LIB_NAME) -o $(APP_NAME) -ltermcap
	@printf "\r\33[2Kush \033[32;1mcreated\033[0m\n"
	@mkdir -p $(OBJ_DIR)
	@mv $(OBJ) $(OBJ_DIR)

uninstall : clean
	@make uninstall -C $(LIBMXF)
	@rm -rf $(APP_NAME)

clean :
	@make clean -C $(LIBMXF)
	@rm -rf $(OBJ_DIR)

reinstall : uninstall install