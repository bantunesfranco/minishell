GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'
BOLD='\033[1m'
INCLUDES="-I incs -I libft/incs"
PARSE_DIR="srcs/parser"
LEX_DIR="srcs/parser/lexer"
#-g -fsanitize=address
# srcs/parser/ft_split_args.c
# -L $HOME/.brew/opt/readline/lib
CFLAGS="-Wall -Werror -Wextra -g -fsanitize=address"
RL_FLAGS=" -lreadline -I $HOME/.brew/opt/readline/include"
SRC="srcs/parser/main_parser.c srcs/ft_arrdup.c srcs/test_utils.c \
srcs/parser/parser.c srcs/parser/parser_init.c srcs/parser/lexer/lex_utils.c \
srcs/parser/lexer/lex.c srcs/parser/lexer/lex_create_tokens.c srcs/parser/lexer/lex_create_token_word.c \
srcs/parser/lexer/lex_assign_groups.c srcs/parser/lexer/lex_validate_syntax.c \
srcs/parser/lexer/lex_token_validation.c srcs/parser/lexer/lex_parenthesis_validation.c"

#!/bin/bash

# compile
rm -rf minishell
cc $CFLAGS $INCLUDES $RL_FLAGS -o minishell libft/libft.a $SRC
./minishell
