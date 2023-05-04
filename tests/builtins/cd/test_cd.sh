RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
END='\033[0m'

#!/bin/bash

`gcc -Wall -Wextra -Werror tests/builtins/cd/cd_main.c srcs/builtins/cd.c srcs/builtins/pwd.c \
srcs/ft_arrdup.c libft/libft.a -I incs -I libft/incs -fsanitize=address -g`

SHELL=`ps -p "$$" | awk 'NR==2{print $4}'`
if [ "$SHELL" == "bash" ]
then
	ECHO="echo -e"
else
	ECHO="echo"
fi

$ECHO "\n	${CYAN}CD TESTER${END}\n----------------------------"

$ECHO "	${MAGENTA}TO STDOUT${END}\n----------------------------"
$ECHO "${BLUE}Test 1 - 'cd'\n${END}"
OUT=`./a.out "pwd" "cd"`
OUT2=`pwd && cd && echo -n "                 " && pwd`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 2 - 'cd -' no OLDPWD\n${END}"
OUT=`./a.out "pwd" "cd -"`
OUT2=`pwd && cd - && echo -n "                 " && pwd`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 3 - 'cd ..'\n${END}"
OUT=`./a.out "pwd" "cd .."`
OUT2=`pwd && cd .. && echo -n "                 " && pwd`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 4 - 'cd .'\n${END}"
OUT=`./a.out "pwd" "cd ."`
OUT2=`pwd && cd . && echo -n "                 " && pwd`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 5 - 'cd incs'\n${END}"
OUT=`./a.out "pwd" "cd incs"`
OUT2=`pwd && cd incs && echo -n "                 " && pwd`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 6 - 'cd /'\n${END}"
OUT=`./a.out "pwd" "cd /"`
OUT2=`pwd && cd / && echo -n "                 " && pwd`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 7 - 'cd -' with OLDPWD\n${END}"

cd .. && cd minishell

OUT=`./a.out "pwd" "cd -"`
OUT2=`pwd && cd - && echo -n "                 " && pwd`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

# `rm -rf a.out`