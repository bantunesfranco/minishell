RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
END='\033[0m'

INCLUDES="-I incs -I libft/incs"
SRCS="tests/builtins/echo/echo_main.c srcs/builtins/echo.c \
srcs/init/ft_arrdup.c srcs/error.c libft/libft.a"

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

$ECHO "\n	${CYAN}ECHO TESTER${END}\n----------------------------"

$ECHO "	${MAGENTA}TO STDOUT${END}\n----------------------------"
$ECHO "${BLUE}Test 1 - 'echo'\n${END}"
OUT=$(./a.out "echo")
OUT2=$(echo)

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
OUT=$(./a.out "echo -n")
OUT2=$(echo -n)

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
OUT=$(./a.out "echo hi")
OUT2=$(echo hi)

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
OUT=$(./a.out "echo -n hi")
OUT2=$(echo -n hi)

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
OUT=$(./a.out "echo -nnnnnnnnnn")
OUT2=$(echo -nnnnnnnnnn)

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
OUT=$(./a.out "echo -nnnnnnnnnn hi")
OUT2=$(echo -nnnnnnnnnn hi)

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
OUT=$(./a.out "echo -nnnnnnnnnnz hi")
OUT2=$(echo -nnnnnnnnnnz hi)

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
OUT=$(./a.out "echo hi this is a test")
OUT2=$(echo hi this is a test)

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
OUT=$(./a.out "echo -n hi this is a test")
OUT2=$(echo -n hi this is a test)

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
OUT=$(./a.out "echo -nnnnnn hi this is a test")
OUT2=$(echo -nnnnnn hi this is a test)

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
OUT=$(./a.out "echo -nnnnnna hi this is a test")
OUT2=$(echo -nnnnnna hi this is a test)

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
OUT=$(./a.out "echo --n hi")
OUT2=$(echo --n hi)

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
OUT=$(./a.out "echo --n")
OUT2=$(echo --n)

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
OUT=$(./a.out "echo --naa")
OUT2=$(echo --naa)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 15 - 'echo -n -n hi test'\n${END}"
OUT=$(./a.out "echo -n -n hi test")
OUT2=$(echo -n -n hi test)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 16 - 'echo -nnnn -nnnn hi test'\n${END}"
OUT=$(./a.out "echo -nnnn -nnnn hi test")
OUT2=$(echo -nnnn -nnnn hi test)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 17 - 'echo -nnnn -nnnna hi test'\n${END}"
OUT=$(./a.out "echo -nnnn -nnnna hi test")
OUT2=$(echo -nnnn -nnnna hi test)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

####################################
#          REDIRECTIONS            #
####################################

$ECHO "	${MAGENTA}TO TXT FILE${END}\n----------------------------"

$ECHO "${BLUE}Test 1 - 'echo'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo" res.txt && < res.txt cat)
OUT2=$(echo > res2.txt && < res2.txt cat)

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 2 - 'echo -n'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo -n" res.txt && < res.txt cat)
OUT2=$(echo -n > res2.txt && < res2.txt cat)

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 3 - 'echo hi'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo hi" res.txt && < res.txt cat)
OUT2=$(echo hi > res2.txt && < res2.txt cat)

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 4 - 'echo -n hi'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo -n hi" res.txt && < res.txt cat)
OUT2=$(echo -n hi > res2.txt && < res2.txt cat)

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 5 - 'echo -nnnnnnnnnn'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo -nnnnnnnnnn" res.txt && < res.txt cat)
OUT2=$(echo -nnnnnnnnnn > res2.txt && < res2.txt cat)

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 6 - 'echo -nnnnnnnnnn hi'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo -nnnnnnnnnn hi" res.txt && < res.txt cat)
OUT2=$(echo -nnnnnnnnnn hi > res2.txt && < res2.txt cat)

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 7 - 'echo -nnnnnnnnnnz hi'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo -nnnnnnnnnnz hi" res.txt && < res.txt cat)
OUT2=$(echo -nnnnnnnnnnz hi && < res2.txt cat)

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 8 - 'echo hi this is a test'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo hi this is a test" res.txt && < res.txt cat)
OUT2=$(echo hi this is a test > res2.txt && < res2.txt cat)

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 9 - 'echo -n hi this is a test'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo -n hi this is a test" res.txt && < res.txt cat)
OUT2=$(echo -n hi this is a test > res2.txt && < res2.txt cat)

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 10 - 'echo -nnnnnn hi this is a test'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo -nnnnnn hi this is a test" res.txt && < res.txt cat)
OUT2=$(echo -nnnnnn hi this is a test > res2.txt && < res2.txt cat)

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 11 - 'echo -nnnnnna hi this is a test'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo -nnnnnna hi this is a test" res.txt && < res.txt cat)
OUT2=$(echo -nnnnnna hi this is a test > res2.txt && < res2.txt cat)

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 12 - 'echo --n hi'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo --n hi" res.txt && < res.txt cat)
OUT2=$(echo --n hi > res2.txt && < res2.txt cat)

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 13 - 'echo --n'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo --n" res.txt && < res.txt cat)
OUT2=$(echo --n > res2.txt && < res2.txt cat)

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

$ECHO "----------------------------"

$ECHO "${BLUE}Test 14 - 'echo --naa'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "echo --naa" res.txt && < res.txt cat)
OUT2=$(echo --naa > res2.txt && < res2.txt cat)

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

$ECHO "----------------------------"

####################################
#         ERROR HANDELING          #
####################################


$ECHO "      ${MAGENTA}ERROR HANDELING${END}\n----------------------------"

$ECHO "${BLUE}Test 1 - 'closed stdout'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(exec 3>&1; exec 1<&-; ./a.out "echo" 2> res.txt; exec 1>&3;\
< res.txt cat | awk -F ': ' '{print $NF}')
OUT2=$(exec 3>&1; exec 1<&-; echo 2> res2.txt; exec 1>&3;\
< res2.txt cat | awk -F ': ' '{print $NF}')

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

$ECHO "----------------------------"

rm -rf a.out
