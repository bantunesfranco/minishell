RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
END='\033[0m'

#!/bin/bash

`gcc -Wall -Wextra -Werror tests/builtins/env/env_main.c srcs/builtins/env.c srcs/ft_arrdup.c libft/libft.a -I incs -I libft/incs` #-fsanitize=address`

SHELL=`ps -p "$$" | awk 'NR==2{print $4}'`
if [ "$SHELL" == "bash" ]
then
	ECHO="echo -e"
else
	ECHO="echo"
fi

$ECHO "\n	${CYAN}ENV TESTER${END}\n----------------------------"

$ECHO "	${MAGENTA}TO STDOUT${END}\n----------------------------"
$ECHO "${BLUE}Test 1 - 'env'\n${END}"
OUT=`./a.out "env" | grep -v _=`
OUT2=`env | grep -v _=`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 2 - 'env env'\n${END}"
OUT=`./a.out "env env" | grep -v _=`
OUT2=""

$ECHO "Do not handle env env. Output should be empty. \n"

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 3 - 'env hi'\n${END}"
OUT=`./a.out "env hi" | grep -v _=`
OUT2=`env hi | grep -v _=`

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

$ECHO "${BLUE}Test 1 - 'env'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "env" res.txt && < res.txt cat | grep -v _=`
OUT2=`env > res2.txt && < res2.txt cat | grep -v _=`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

`rm -rf res.txt`
`rm -rf res2.txt`

$ECHO "----------------------------"

$ECHO "${BLUE}Test 2 - 'env env'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

$ECHO "Do not handle env env. Output should be empty. \n"

OUT=`./a.out "env env" res.txt && < res.txt cat | grep -v _=`
OUT2=""

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

`rm -rf res.txt`
`rm -rf res2.txt`

$ECHO "----------------------------"

$ECHO "${BLUE}Test 3 - 'env hi'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "env hi" res.txt && < res.txt cat | grep -v _=`
OUT2=`env hi > res2.txt && < res2.txt cat | grep -v _=`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

`rm -rf res.txt`
`rm -rf res2.txt`

$ECHO "----------------------------"

`rm -rf a.out`
