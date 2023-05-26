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
CFLAGSD="-Wall -Werror -Wextra -g -fsanitize=address"
RL_FLAGS=" -lreadline -I $HOME/.brew/opt/readline/include"
SRC="srcs/input_parser/main_parser.c srcs/ft_arrdup.c srcs/test_utils.c \
srcs/input_parser/input_parser.c srcs/input_parser/parser_struct_init.c srcs/input_parser/token_list_functions.c \
srcs/input_parser/lexer/*  \
srcs/input_parser/pipeline_list_functions.c \
srcs/input_parser/simple_cmd_list_functions.c \
srcs/input_parser/redirect_list_functions.c \
srcs/input_parser/parser/*"

#!/bin/bash

help_func(){
	echo -e "\n\nrun - start minishell"
	echo "debug - start minishell with fsanitize"
	echo "sy - run syntax error tests"
	echo "le - run lexer tests"
	echo "help - display this message"
	echo "exit - exit tester"
	echo ""
}

help_arg(){
	echo -e "\n\nrun - start minishell"
	echo "debug - start minishell with fsanitize"
	echo "sy - run syntax error tests"
	echo "le - run lexer tests"
	echo "help - display this message"
	echo ""
}

readinput(){
	clear
	echo -e "\n${BOLD}What mode would you like to run :${RESET}"
	help_func
	echo -e ""
	while [[ $option != "exit" ]]
	do
		read option
		if [[ $option == "run" ]]
		then
			run_minishell
			help_func
		elif [[ $option == "debug" ]]
		then
			run_debug_minishell
			help_func
		elif [[ $option == "sy" ]]
		then
			echo -e "\n		${BOLD}${GREEN}Testing syntax errors${RESET}\n"
			test_syntax
			help_func
		elif [[ $option == "le" ]]
		then
			echo -e "\n		${BOLD}${GREEN}Testing lexer${RESET}\n"
			test_lexer
			help_func
		elif [[ $option == "help" ]]
		then
			help_func
		elif [[ $option == "exit" ]]
		then
			break ;
		else
			echo -e "\nPlease input valid option"
			echo "help - for valid options"
		fi
		echo ""
	done
}

runoption(){
	if [[ $1 == "run" ]]
	then
		run_minishell
	elif [[ $1 == "debug" ]]
	then
		run_debug_minishell
	elif [[ $1 == "sy" ]]
	then
		echo -e "\n		${BOLD}${GREEN}Testing syntax errors${RESET}\n"
		test_syntax
	elif [[ $1 == "le" ]]
	then
		echo -e "\n		${BOLD}${GREEN}Testing lexer${RESET}\n"
		test_lexer
	elif [[ $1 == "help" ]]
	then
		echo -e "\n\n${BOLD}Run ./parsing_test.sh with one of the following arguments or none for interactive input${RESET}"
		help_arg
	else
		echo -e "\n\n${BOLD}Run ./parsing_test.sh with one of the following arguments or none for interactive input${RESET}"
		help_arg
	fi
	echo ""
}

main () {
	if [[ $# == 0 ]]
	then
		readinput
	else
		runoption $1
	fi
}

run_minishell () {
	rm -rf minishell
	cc $CFLAGS $INCLUDES $RL_FLAGS -o minishell libft/libft.a $SRC
	./minishell
}

run_debug_minishell () {
	rm -rf minishell
	cc $CFLAGSD $INCLUDES $RL_FLAGS -o minishell libft/libft.a $SRC
	./minishell
}

test_syntax () {
	./testers_j/syntax_error.sh
}

test_lexer () {
	./testers_j/lexer_tester.sh
}

# ./minishell

main $1
