GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'
BOLD='\033[1m'
CFLAGS="-Wall -Werror -Wextra"
INCLUDES="-I incs -I libft/incs"
SRC="srcs/input_parser/expansion/expansion.c \
testers_j/expansion_test.c \
libft/libft.a \
srcs/init/env_init.c \
srcs/error.c \
srcs/utils.c \
srcs/test_utils.c"

#!/bin/bash

test_output () {
	echo -n "Output :   "
	if [[ $1 == $2 ]]
	then
		echo -e -n "${GREEN}OK🌟   ${RESET}"
	else
		echo -e -n "${RED}KO🤢   ${RESET}"
		((KO++))
		echo -e "different errors for argument: \n$TEST" >> error_args
	fi
}

test_err () {
	echo -n "Error :   "
	if [[ ! -s $1 ]]
	then
		echo -e "${GREEN}OK🌟\n${RESET}"
	else
		echo -e "${RED}KO🤢\n${RESET}"
		((KO++))
		echo -e "different errors for argument: \n$TEST" >> error_args
	fi
}

rm -rf minishell
cc $CFLAGS $INCLUDES -o minishell libft/libft.a $SRC
# echo "--------------------------------------------------------------------------"
# echo -e "------------------------------${GREEN}STARTING TESTS${RESET}------------------------------"
# echo "--------------------------------------------------------------------------"	
sleep 2
FILE="./testers_j/files/expansion"
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
		# echo -e "	Test for input :\n👉	$line"
		OUTPUT=$(./minishell $line 2>err_mini)
		echo $OUTPUT
		# read -r line
		# test_output $OUTPUT $line
		# test_err err_mini
		# test_code $exit_mini $exit_bash
	fi
done < "$FILE"
# if [[ $KO == 0 ]]
# then
# 	echo -e "\n	👍${GREEN}TESTS PASSED${RESET}\n"
# else
# 	echo -e "\n	🤮${RED}${KO} TESTS FAILED${RESET}\n"
# fi
rm err_mini

