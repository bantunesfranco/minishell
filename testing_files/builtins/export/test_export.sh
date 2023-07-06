RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
END='\033[0m'

INCLUDES="-I incs -I libft/incs"
SRCS="tests/builtins/export/export_main.c srcs/builtins/export.c srcs/builtins/export2.c
srcs/builtins/env.c srcs/init/ft_arrdup.c srcs/utils.c srcs/error.c libft/libft.a"


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

$ECHO "\n       ${CYAN}EXPORT TESTER${END}\n----------------------------"

$ECHO "	 ${MAGENTA}TO STDOUT${END}\n----------------------------"
$ECHO "${BLUE}Test 1 - 'export'\n${END}"
OUT=$(./a.out env "export")
OUT2=$(export)

# $ECHO "minishell:	|$OUT|\n"
# $ECHO "bash: 		|$OUT2|"

if [ "$OUT" != "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 2 - 'export HI=2'\n${END}"
OUT=$(./a.out env "export HI=2" | grep HI=)
OUT2=$(export HI=2; env | grep HI=)

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
OUT=$(./a.out env "export HOME=reeee" | grep HOME=)
OUT2=$(export HOME=reeee; env | grep HOME=)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 4 - 'export HOME=reeee BOB=bob'\n${END}"
OUT=$(./a.out env "export HOME=reeee BOB=bob" | (grep HOME= && grep BOB=))
OUT2=$(export HOME=reeee BOB=bob; env | (grep HOME= && grep BOB=))

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 5 - 'export BOB=bob BOB+=hello'\n${END}"

OUT=$(./a.out env "export BOB=bob BOB+=hello" | grep BOB=)
OUT2=$(export BOB=bob BOB+=hello; env | grep BOB=)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 6 - 'export BANANA+=hello'\n${END}"

unset BANANA

OUT=$(./a.out env "export BANANA+=hello" | grep BANANA=)
OUT2=$(export BANANA+=hello; env | grep BANANA=)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 7 - 'export BANANA+=hello BANANA+=hello BANANA+=hello'\n${END}"

unset BANANA

OUT=$(./a.out env "export BANANA+=hello BANANA+=hello BANANA+=hello" | grep BANANA=)
OUT2=$(export BANANA+=hello BANANA+=hello BANANA+=hello; env | grep BANANA=)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 8 - 'export BANANA=hello HELLO BANANA+=nope'\n${END}"

$(unset BANANA)

OUT=$(./a.out env "export BANANA=hello HELLO BANANA+=nope" | (grep BANANA= && grep HELLO))
OUT2=$(export BANANA=hello HELLO BANANA+=nope; env | (grep BANANA= && grep HELLO))

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 9 - 'export HI HELLO HO='\n${END}"

OUT=$(./a.out env "export HI HELLO HO=" | grep HO=)
OUT2=$(export export HI HELLO HO=; env | grep HO=)

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

$(touch res.txt && chmod 777 res.txt)
$(touch res2.txt && chmod 777 res2.txt)

OUT=$(./a.out env "export" res.txt && < res.txt cat)
OUT2=$(export > res2.txt && < res2.txt cat)

# $ECHO "minishell:	|$OUT|\n"
# $ECHO "bash: 		|$OUT2|"

if [ "$OUT" != "$OUT2" ];
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

$(touch res.txt && chmod 777 res.txt)

OUT=$(exec 3>&1; exec 1<&-; ./a.out "env" "export" 2> res.txt; exec 1>&3;\
< res.txt cat | awk -F ': ' '{print $NF}')
OUT2="Bad file descriptor"

$ECHO "Bash doesn not print any errors, but we do\n"

$ECHO "minishell:	|$OUT|"
# $ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

rm -rf res.txt
rm -rf res2.txt

$ECHO "----------------------------"

$ECHO "${BLUE}Test 2 - 'export HI HELLO HO!='\n${END}"

$(touch res.txt && chmod 777 res.txt)
$(touch res2.txt && chmod 777 res2.txt)

OUT=$(./a.out env "export HI HELLO HO!=" > /dev/null 2> res.txt; \
< res.txt cat | awk -F ': ' '{print $NF}')
OUT2=$(export HI HELLO HO!= 2> res2.txt; <\
 res2.txt cat | awk -F ': ' '{print $NF}')

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

$ECHO "${BLUE}Test 3 - 'export HI HELLO HO-='\n${END}"

$(touch res.txt && chmod 777 res.txt)
$(touch res2.txt && chmod 777 res2.txt)
unset HO

OUT=$(./a.out env "export HI HELLO HO-=" > /dev/null 2> res.txt; \
< res.txt cat | awk -F ': ' '{print $NF}')
OUT2=$(export HI HELLO HO-= 2> res2.txt; <\
 res2.txt cat | awk -F ': ' '{print $NF}')

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

$ECHO "${BLUE}Test 4 - 'export -'\n${END}"

$(touch res.txt && chmod 777 res.txt)
$(touch res2.txt && chmod 777 res2.txt)

OUT=$(./a.out env "export -" > /dev/null 2> res.txt; \
< res.txt cat | awk -F ': ' '{print $NF}')
OUT2=$(export - 2> res2.txt; <\
 res2.txt cat | awk -F ': ' '{print $NF}')

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

$(rm -rf a.out)
