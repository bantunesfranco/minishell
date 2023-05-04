RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
END=\033[0m

NAME = minishell
SRC_FILES = main.c ft_arrdup.c
OBJ_FILES = $(SRC_FILES:%.c=obj/%.o)
OBJ_DIR = obj obj/parser


# readline flags
RL_FLAGS = -L $(HOME)/.brew/opt/readline/lib -lreadline -I $(HOME)/.brew/opt/readline/include

# libft variables
LIBFT = libft/libft.a
LIBFT_DIR = libft

# compilation variables
CC = cc
INCLUDES = -I incs -I libft/incs
ifdef DEBUG
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
else
CFLAGS = -Wall -Werror -Wextra
endif

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	OBJ_FLAGS := $(RL_FLAGS)
else ifeq ($(UNAME_S), Darwin)
	OBJ_FLAGS := 
else
	$(error OS: $(OS) is not supported!)
endif

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	@echo "${MAGENTA}Creating $@${END}"
	@$(CC) $(INCLUDES) $(RL_FLAGS) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT)
	@echo "${GREEN}Done!${END}"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

obj/%.o: srcs/%.c | $(OBJ_DIR)
	@echo "${BLUE}Compiling $<${END}"
	@$(CC) $(INCLUDES) $(OBJ_FLAGS) $(CFLAGS) -c -o $@ $^

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@echo "${RED}Removing objs minishell${END}"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "${RED}Removing ${NAME} and $(LIBFT)${END}"
	@rm -rf $(LIBFT) $(NAME)

debug: fclean
	@$(MAKE) DEBUG=1 all

re: fclean all