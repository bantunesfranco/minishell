RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
END='\033[0m'

#!/bin/bash

`gcc -Wall -Wextra -Werror tests/builtins/pwd/pwd_main.c srcs/builtins/pwd.c srcs/utils.c srcs/ft_arrdup.c libft/libft.a -I incs -I libft/incs` #-fsanitize=address`

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 2 - 'pwd hello\n${END}"
OUT=`./a.out "pwd hello"`
OUT2=`pwd hello`

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
$ECHO "${BLUE}Test 1 - 'pwd'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "pwd" res.txt > res.txt && cat res.txt`
OUT2=`pwd > res2.txt && cat res2.txt`

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

$ECHO "${BLUE}Test 2 - 'pwd hello\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "pwd hello" res.txt > res.txt && cat res.txt`
OUT2=`pwd hello > res2.txt && cat res2.txt`

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

####################################
#         ERROR HANDELING          #
####################################

$ECHO "      ${MAGENTA}ERROR HANDELING${END}\n----------------------------"

$ECHO "${BLUE}Test 1 - 'closed stdout'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`exec 3>&1; exec 1<&-; ./a.out "pwd" 2> res.txt; exec 1>&3;\
< res.txt cat | awk -F ': ' '{sub($1 FS, ""); print}'`
OUT2=`exec 3>&1; exec 1<&-; pwd 2> res2.txt; exec 1>&3; < res2.txt cat\
| awk -F ': ' '{sub($1 FS, ""); sub($1 FS, ""); print}'`

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


`rm -rf a.out`
