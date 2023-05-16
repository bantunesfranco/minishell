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
CFLAGS="-Wall -Werror -Wextra"
RL_FLAGS=" -lreadline -I $HOME/.brew/opt/readline/include"
SRC="srcs/input_parser/main_parser.c srcs/ft_arrdup.c srcs/test_utils.c \
srcs/input_parser/input_parser.c srcs/input_parser/parser_struct_init.c srcs/input_parser/lexer/lex_utils.c \
srcs/input_parser/lexer/lex.c srcs/input_parser/lexer/lex_create_tokens.c srcs/input_parser/lexer/lex_create_token_word.c \
srcs/input_parser/lexer/lex_assign_groups.c srcs/input_parser/lexer/lex_validate_syntax.c \
srcs/input_parser/lexer/lex_token_validation.c srcs/input_parser/lexer/lex_parenthesis_validation.c \
srcs/input_parser/lexer/lex_error_functions.c \
srcs/input_parser/parser/par.c"

#!/bin/bash


rm -rf minishell

main () {
	cc $CFLAGS $INCLUDES $RL_FLAGS -o minishell libft/libft.a $SRC
	echo "--------------------------------------------------------------------------"
	echo -e "------------------------------${GREEN}STARTING TESTS${RESET}------------------------------"
	echo "--------------------------------------------------------------------------"
	if [[ $1 == "com" ]]
	then
	./minishell
	elif [[ $1 == "sy" ]]
	then
	echo -e "\n		${BOLD}${GREEN}Testing syntax errors${RESET}\n"
	test_syntax
	else
	echo "usage:"
	echo "./test_paser.sh [option, sy]"
	echo "sy: syntax tests"
	fi
}

test_syntax () {
	./testers_j/syntax_error.sh
}
# ./minishell

main $1
