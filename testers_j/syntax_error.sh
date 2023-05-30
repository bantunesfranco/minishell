GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'
BOLD='\033[1m'
CFLAGS="-Wall -Werror -Wextra"
INCLUDES="-I incs -I libft/incs"
SRC="srcs/input_parser/lexer/* srcs/input_parser/parser_struct_init.c srcs/input_parser/token_list_functions.c \
testers_j/syntax_tester.c srcs/test_utils.c srcs/error.c"

#!/bin/bash

# functions comparing output, error and error code

test_output(){
	echo -n "Output :   "
	if ! diff -q $1 $2 >/dev/null
	then
		echo -e -n  "${RED}KO🤢   ${RESET}"
		((KO++))
		echo -e "different outputs for argument: \n$TEST" >> error_args
	else
		echo -e -n "${GREEN}OK🌟   ${RESET}"
	fi
}

test_err(){
	echo -n "Error :   "
	if [[ -s $1 && -s $2 ]] || [[ ! -s $1 && ! -s $2 ]]
	then
		echo -e "${GREEN}OK🌟\n${RESET}"
	else
		echo -e "${RED}KO🤢\n${RESET}"
		((KO++))
		echo -e "different errors for argument: \n$TEST" >> error_args
	fi
}

test_code(){
	echo $1 $2
	if [[ $1 == $2 ]]
	then
		echo -e "${GREEN}OK${RESET}"
	else
		echo -e "${RED}KO${RESET}"
	fi
}

# script

rm -rf minishell
cc $CFLAGS $INCLUDES -o minishell libft/libft.a $SRC
echo "--------------------------------------------------------------------------"
echo -e "------------------------------${GREEN}STARTING TESTS${RESET}------------------------------"
echo "--------------------------------------------------------------------------"	
sleep 2
FILE="./testers_j/files/syntax_errors"
IFS=0
NL=$'\n'
KO=0
rm -rf error_args
	while read -r line
	do
		if [[ $line == "" ]]
		then
			continue
		else
			while [[ $line != "" ]]
			do
				TEST+="$line$NL"
				read -r line
			done
		fi
		echo -e -n "	Test for input :\n👉	$TEST"
		./minishell $TEST 2>err_mini >out_mini
		exit_mini=$?
		echo -n "$TEST" | bash 2>err_bash >out_bash
		exit_bash=$?
		test_output out_mini out_bash
		test_err err_mini err_bash
		# test_code $exit_mini $exit_bash
		TEST=""
	done < "$FILE"
if [[ $KO == 0 ]]
then
	echo -e "\n	👍${GREEN}TESTS PASSED${RESET}\n"
else
	echo -e "\n	🤮${RED}${KO} TESTS FAILED${RESET}\n"
fi
rm -f err_*
rm -f out_*
