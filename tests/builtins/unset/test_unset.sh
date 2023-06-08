RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
END='\033[0m'

INCLUDES="-I incs -I libft/incs"
SRCS="tests/builtins/unset/unset_main.c srcs/builtins/unset.c srcs/builtins/env.c \
srcs/init/ft_arrdup.c srcs/utils.c srcs/error.c libft/libft.a"

CFLAGS="-Wall -Werror -Wextra"
# CFLAGSD="-Wall -Werror -Wextra -g -fsanitize=address"

#!/bin/bash

gcc $CFLAGS $SRCS $INCLUDES -o a.out

SHELL=$(ps -p "$$" | awk 'NR==2{print $4}')
if [ "$SHELL" == "bash" ]
then
	ECHO="echo -e"
else
	ECHO="echo"
fi

$ECHO "\n	${CYAN}ENV TESTER${END}\n----------------------------"

$ECHO "	${MAGENTA}TO STDOUT${END}\n----------------------------"
$ECHO "${BLUE}Test 1 - 'unset'\n${END}"
OUT=$(./a.out env "unset" | grep -v _=)
OUT2=$(unset; env | grep -v _=)

$ECHO "minishell:	|$OUT|\n"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 2 - 'unset HI'\n${END}"
OUT=$(./a.out env "unset HI" | grep HI=)
OUT2=$(unset HI; env | grep HI=)

$ECHO "minishell:	|$OUT|\n"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 3 - 'unset HOME'\n${END}"
OUT=$(./a.out env "unset HOME" | grep HOME=)
OUT2=$(unset HOME; env | grep HOME=)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 4 - 'unset HOME='\n${END}"
OUT=$(./a.out env "unset HOME=" | grep HOME=)
unset HOME=
OUT2=$(env | grep HOME=)

$ECHO "minishell:	|$OUT|\n"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$(rm -rf a.out)
