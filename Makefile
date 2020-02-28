APP_NAME = ush

LIBMXF = libmx

LIB_NAME = libmx.a

INC = \
inc/ \
libmx/inc/

SRC_DIR = src

OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/,\
	builds/cd.c \
	builds/ls.c \
	builds/pwd.c \
	input/mx_process_input.c \
	printing/mx_print_prompt.c \
	main/mx_create_main.c \
	main/main.c)

OBJ = \
	cd.o \
	ls.o \
	pwd.o \
	mx_process_input.o \
	mx_print_prompt.o \
	mx_create_main.o \
	main.o
CC = clang

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all : install

install : libmx/libmx.a uls

libmx/libmx.a:
	@make -C $(LIBMXF)

uls : $(SRC) inc/ush.h libmx/libmx.a
	@$(CC) $(CFLAGS) -c $(SRC) $(foreach d, $(INC), -I $d)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBMXF)/$(LIB_NAME) -o $(APP_NAME)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"
	@mkdir -p $(OBJ_DIR)
	@mv $(OBJ) $(OBJ_DIR)

uninstall : clean
	@make uninstall -C $(LIBMXF)
	@rm -rf $(APP_NAME)

clean :
	@make clean -C $(LIBMXF)
	@rm -rf $(OBJ_DIR)

reinstall : uninstall install