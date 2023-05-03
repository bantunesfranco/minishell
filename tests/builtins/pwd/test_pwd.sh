RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
END='\033[0m'

#!/bin/bash

`gcc -Wall -Wextra -Werror tests/builtins/pwd/pwd_main.c srcs/builtins/pwd.c srcs/ft_arrdup.c libft/libft.a -I incs -I libft/incs -fsanitize=leak`

SHELL=`ps -p "$$" | awk 'NR==2{print $4}'`
if [ "$SHELL" == "bash" ]
then
	ECHO="echo -e"
else
	ECHO="echo"
fi

$ECHO "\n	${CYAN}PWD TESTER${END}\n----------------------------"

$ECHO "	${MAGENTA}TO STDOUT${END}\n----------------------------"
$ECHO "${BLUE}Test 1 - 'pwd'\n${END}"
OUT=`./a.out "pwd"`
OUT2=`pwd`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

rm -rf a.out

$ECHO "----------------------------"

`gcc -Wall -Wextra -Werror tests/builtins/pwd/pwd_main2.c srcs/builtins/pwd.c srcs/ft_arrdup.c libft/libft.a -I incs -I libft/incs -fsanitize=leak`

$ECHO "${BLUE}Test 2 - 'pwd with cd'\n${END}"
OUT=`./a.out "pwd"`
OUT2=`pwd && cd .. && echo -n "                 " && pwd`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

rm -rf a.out

$ECHO "----------------------------"

$ECHO "	${MAGENTA}TO TXT FILE${END}\n----------------------------"
$ECHO "${BLUE}Test 1 - 'pwd'\n${END}"

`gcc -Wall -Wextra -Werror tests/builtins/pwd/pwd_main3.c srcs/builtins/pwd.c srcs/ft_arrdup.c libft/libft.a -I incs -I libft/incs -fsanitize=leak`

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "pwd" > res.txt && cat res.txt`
OUT2=`pwd > res2.txt && cat res2.txt`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

rm -rf res.txt
rm -rf res2.txt
rm -rf a.out

$ECHO "----------------------------"