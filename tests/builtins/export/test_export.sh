RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
END='\033[0m'

#!/bin/bash

`gcc -Wall -Wextra -Werror tests/builtins/export/export_main.c srcs/builtins/export.c srcs/builtins/export2.c srcs/builtins/env.c srcs/ft_arrdup.c srcs/utils.c libft/libft.a -I incs -I libft/incs -fsanitize=address`

SHELL=`ps -p "$$" | awk 'NR==2{print $4}'`
if [ "$SHELL" == "bash" ]
then
	ECHO="echo -e"
else
	ECHO="echo"
fi

$ECHO "\n	${CYAN}ENV TESTER${END}\n----------------------------"

$ECHO "	${MAGENTA}TO STDOUT${END}\n----------------------------"
$ECHO "${BLUE}Test 1 - 'export'\n${END}"
OUT=`./a.out env "export"`
OUT2=`export`

$ECHO "minishell:	|$OUT|\n"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" != "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 2 - 'export HI=2'\n${END}"
OUT=`./a.out env "export HI=2" | grep HI=`
OUT2=`export HI=2; env | grep HI=`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 3 - 'export HOME=reeee'\n${END}"
OUT=`./a.out env "export HOME=reeee" | grep HOME=`
OUT2=`export HOME=reeee; env | grep HOME=`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "	${MAGENTA}TO TXT FILE${END}\n----------------------------"

$ECHO "${BLUE}Test 1 - 'export'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out env "export" res.txt && < res.txt cat`
OUT2=`export > res2.txt && < res2.txt cat`

$ECHO "minishell:	|$OUT|\n"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" != "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

`rm -rf res.txt`
`rm -rf res2.txt`

$ECHO "----------------------------"

`rm -rf a.out`
