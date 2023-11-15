RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
END=\033[0m

NAME = lexer_test syntax_test parser_test expansion_test
SRC_FILES = $(shell find ../srcs -type f -name "*.c")
OBJ_FILES = $(SRC_FILES:../srcs/%.c=../obj/%.o)
OBJ_DIR = ../obj ../obj/input_parser ../obj/builtins ../obj/init ../obj/executor ../obj/input_parser/lexer  ../obj/input_parser/list_functions ../obj/input_parser/parser ../obj/executor/expansion
HEADERS  = $(shell find ../incs -type f -name "*.h")

# readline flags
RL_FLAGS = -L $(HOME)/.brew/opt/readline/lib -lreadline

# libft variables
LIBFT = ../libft/libft.a
LIBFT_DIR = ../libft

# compilation variables
CC = cc
INCLUDES = -I ../incs -I ../libft/incs
ifdef DEBUG
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
else
CFLAGS = -Wall -Werror -Wextra
endif

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	RL_FLAGS = -lreadline -ltinfo
else ifeq ($(UNAME_S), Darwin)
	READLINE = $(shell brew --prefix readline)
	RL_FLAGS = -L $(READLINE)/lib -lreadline
	INCLUDES += -I $(READLINE)/include
else
	$(error OS: $(OS) is not supported!)
endif

# ifeq ($(UNAME_S), Linux)
# 	OBJ_FLAGS := $(RL_FLAGS)
# else ifeq ($(UNAME_S), Darwin)
# 	OBJ_FLAGS := 
# else
# 	$(error OS: $(OS) is not supported!)
# endif

# compilation files for all the various tests

COM_LEXER = ../obj/input_parser/lexer/* ../obj/input_parser/list_functions/token_list_functions.o ../obj/utils.o \
c_files/lexer_tester.c ../obj/error.o ../obj/input_parser/input_parser_utils.o

COM_SYNTAX = ../obj/input_parser/lexer/* ../obj/input_parser/list_functions/token_list_functions.o \
c_files/syntax_tester.c ../obj/error.o ../obj/input_parser/input_parser_utils.o ../obj/utils.o

lexer_test: comfiles
	$(CC) $(CFLAGS) -o $@ $(COM_LEXER) $(INCLUDES) $(LIBFT) $(RL_FLAGS)

syntax_test: comfiles
	$(CC) $(CFLAGS) -o $@ $(COM_SYNTAX) $(INCLUDES) $(LIBFT) $(RL_FLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

comfiles: $(LIBFT) $(OBJ_FILES)

../obj/%.o: ../srcs/%.c $(HEADERS) | $(OBJ_DIR)
	@$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "${RED}Removing binaries${END}"
	@rm -rf $(LIBFT) $(NAME)
