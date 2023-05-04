RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
END='\033[0m'

#!/bin/bash

`gcc -Wall -Wextra -Werror tests/builtins/echo/echo_main.c srcs/builtins/echo.c srcs/ft_arrdup.c libft/libft.a -I incs -I libft/incs -fsanitize=address`

SHELL=`ps -p "$$" | awk 'NR==2{print $4}'`
if [ "$SHELL" == "bash" ]
then
	ECHO="echo -e"
else
	ECHO="echo"
fi

$ECHO "\n	${CYAN}ECHO TESTER${END}\n----------------------------"

$ECHO "	${MAGENTA}TO STDOUT${END}\n----------------------------"
$ECHO "${BLUE}Test 1 - 'echo'\n${END}"
OUT=`./a.out "echo"`
OUT2=`echo`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 2 - 'echo -n'\n${END}"
OUT=`./a.out "echo -n"`
OUT2=`echo -n`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 3 - 'echo hi'\n${END}"
OUT=`./a.out "echo hi"`
OUT2=`echo hi`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 4 - 'echo -n hi'\n${END}"
OUT=`./a.out "echo -n hi"`
OUT2=`echo -n hi`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 5 - 'echo -nnnnnnnnnn'\n${END}"
OUT=`./a.out "echo -nnnnnnnnnn"`
OUT2=`echo -nnnnnnnnnn`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 6 - 'echo -nnnnnnnnnn hi'\n${END}"
OUT=`./a.out "echo -nnnnnnnnnn hi"`
OUT2=`echo -nnnnnnnnnn hi`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 7 - 'echo -nnnnnnnnnnz hi'\n${END}"
OUT=`./a.out "echo -nnnnnnnnnnz hi"`
OUT2=`echo -nnnnnnnnnnz hi`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 8 - 'echo hi this is a test'\n${END}"
OUT=`./a.out "echo hi this is a test"`
OUT2=`echo hi this is a test`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 9 - 'echo -n hi this is a test'\n${END}"
OUT=`./a.out "echo -n hi this is a test"`
OUT2=`echo -n hi this is a test`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 10 - 'echo -nnnnnn hi this is a test'\n${END}"
OUT=`./a.out "echo -nnnnnn hi this is a test"`
OUT2=`echo -nnnnnn hi this is a test`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 11 - 'echo -nnnnnna hi this is a test'\n${END}"
OUT=`./a.out "echo -nnnnnna hi this is a test"`
OUT2=`echo -nnnnnna hi this is a test`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 12 - 'echo --n hi'\n${END}"
OUT=`./a.out "echo --n hi"`
OUT2=`echo --n hi`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 13 - 'echo --n'\n${END}"
OUT=`./a.out "echo --n"`
OUT2=`echo --n`

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 14 - 'echo --naa'\n${END}"
OUT=`./a.out "echo --naa"`
OUT2=`echo --naa`

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

$ECHO "${BLUE}Test 1 - 'echo'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo" res.txt && < res.txt cat`
OUT2=`echo > res2.txt && < res2.txt cat`

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

$ECHO "${BLUE}Test 2 - 'echo -n'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo -n" res.txt && < res.txt cat`
OUT2=`echo -n > res2.txt && < res2.txt cat`

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

$ECHO "${BLUE}Test 3 - 'echo hi'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo hi" res.txt && < res.txt cat`
OUT2=`echo hi > res2.txt && < res2.txt cat`

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

$ECHO "${BLUE}Test 4 - 'echo -n hi'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo -n hi" res.txt && < res.txt cat`
OUT2=`echo -n hi > res2.txt && < res2.txt cat`

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

$ECHO "${BLUE}Test 5 - 'echo -nnnnnnnnnn'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo -nnnnnnnnnn" res.txt && < res.txt cat`
OUT2=`echo -nnnnnnnnnn > res2.txt && < res2.txt cat`

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

$ECHO "${BLUE}Test 6 - 'echo -nnnnnnnnnn hi'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo -nnnnnnnnnn hi" res.txt && < res.txt cat`
OUT2=`echo -nnnnnnnnnn hi > res2.txt && < res2.txt cat`

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

$ECHO "${BLUE}Test 7 - 'echo -nnnnnnnnnnz hi'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo -nnnnnnnnnnz hi" res.txt && < res.txt cat`
OUT2=`echo -nnnnnnnnnnz hi && < res2.txt cat`

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

$ECHO "${BLUE}Test 8 - 'echo hi this is a test'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo hi this is a test" res.txt && < res.txt cat`
OUT2=`echo hi this is a test > res2.txt && < res2.txt cat`

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

$ECHO "${BLUE}Test 9 - 'echo -n hi this is a test'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo -n hi this is a test" res.txt && < res.txt cat`
OUT2=`echo -n hi this is a test > res2.txt && < res2.txt cat`

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

$ECHO "${BLUE}Test 10 - 'echo -nnnnnn hi this is a test'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo -nnnnnn hi this is a test" res.txt && < res.txt cat`
OUT2=`echo -nnnnnn hi this is a test > res2.txt && < res2.txt cat`

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

$ECHO "${BLUE}Test 11 - 'echo -nnnnnna hi this is a test'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo -nnnnnna hi this is a test" res.txt && < res.txt cat`
OUT2=`echo -nnnnnna hi this is a test > res2.txt && < res2.txt cat`

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

$ECHO "${BLUE}Test 12 - 'echo --n hi'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo --n hi" res.txt && < res.txt cat`
OUT2=`echo --n hi > res2.txt && < res2.txt cat`

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

$ECHO "${BLUE}Test 13 - 'echo --n'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo --n" res.txt && < res.txt cat`
OUT2=`echo --n > res2.txt && < res2.txt cat`

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

$ECHO "${BLUE}Test 14 - 'echo --naa'\n${END}"

`touch res.txt && chmod 777 res.txt`
`touch res2.txt && chmod 777 res2.txt`

OUT=`./a.out "echo --naa" res.txt && < res.txt cat`
OUT2=`echo --naa > res2.txt && < res2.txt cat`

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
