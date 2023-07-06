RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
END='\033[0m'

INCLUDES="-I incs -I libft/incs"
SRCS="tests/builtins/exit/exit_main.c srcs/builtins/exit.c \
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

$ECHO "\n	${CYAN}EXIT TESTER${END}\n----------------------------"

$ECHO "	 ${MAGENTA}TO STDOUT${END}\n----------------------------"
$ECHO "${BLUE}Test 1 - 'exit'\n${END}"

$(touch res.txt && chmod 777 res.txt)
$(touch res2.txt && chmod 777 res2.txt)

CODE=$(./a.out exit 2> res.txt; echo $?)
CODE2=$( (exit 2> res2.txt); echo $?)
OUT= < res.txt cat
OUT= < res2.txt cat
echo -e "me: $CODE\nbash: $CODE2" 
if [ "$OUT" == "$OUT2" ] && [ "$CODE" == "$CODE2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

rm -rf res.txt
rm -rf res2.txt

$ECHO "----------------------------"

$ECHO "${BLUE}Test 2 - 'exit 1'\n${END}"

$(touch res.txt && chmod 777 res.txt)
$(touch res2.txt && chmod 777 res2.txt)

CODE=$(./a.out "exit 1" 2> res.txt; echo $?)
CODE2=$( (exit 1 2> res2.txt); echo $?)
OUT= < res.txt cat
OUT= < res2.txt cat
echo -e "me: $CODE\nbash: $CODE2" 
if [ "$OUT" == "$OUT2" ] && [ "$CODE" == "$CODE2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

rm -rf res.txt
rm -rf res2.txt

$ECHO "----------------------------"

$ECHO "${BLUE}Test 3 - 'exit 200'\n${END}"

$(touch res.txt && chmod 777 res.txt)
$(touch res2.txt && chmod 777 res2.txt)

CODE=$(./a.out "exit 200" 2> res.txt; echo $?)
CODE2=$( (exit 200 2> res2.txt); echo $?)
OUT= < res.txt cat
OUT= < res2.txt cat
echo -e "me: $CODE\nbash: $CODE2" 
if [ "$OUT" == "$OUT2" ] && [ "$CODE" == "$CODE2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

rm -rf res.txt
rm -rf res2.txt

$ECHO "----------------------------"

$ECHO "${BLUE}Test 4 - 'exit 500'\n${END}"

$(touch res.txt && chmod 777 res.txt)
$(touch res2.txt && chmod 777 res2.txt)

CODE=$(./a.out "exit 500" 2> res.txt; echo $?)
CODE2=$( (exit 500 2> res2.txt); echo $?)
OUT= < res.txt cat
OUT= < res2.txt cat
echo -e "me: $CODE\nbash: $CODE2" 
if [ "$OUT" == "$OUT2" ] && [ "$CODE" == "$CODE2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

rm -rf res.txt
rm -rf res2.txt

$ECHO "----------------------------"

$ECHO "${BLUE}Test 5 - 'exit -500'\n${END}"

$(touch res.txt && chmod 777 res.txt)
$(touch res2.txt && chmod 777 res2.txt)

CODE=$(./a.out "exit -500" 2> res.txt; echo $?)
CODE2=$( (exit -500 2> res2.txt); echo $?)
OUT= < res.txt cat
OUT= < res2.txt cat
echo -e "me: $CODE\nbash: $CODE2" 
if [ "$OUT" == "$OUT2" ] && [ "$CODE" == "$CODE2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

rm -rf res.txt
rm -rf res2.txt

$ECHO "----------------------------"

# ###################################
#         ERROR HANDELING          #
# ###################################

# $ECHO "      ${MAGENTA}ERROR HANDELING${END}\n----------------------------"

# $ECHO "${BLUE}Test 1 - 'closed stdout'\n${END}"

# $(touch res.txt && chmod 777 res.txt)

# OUT=$(exec 3>&1; exec 1<&-; ./a.out "env" "export" 2> res.txt; exec 1>&3;\
# < res.txt cat | awk -F ': ' '{sub($1 FS, ""); print}')
# OUT2="export: write error: Bad file descriptor"

# $ECHO "Bash doesn not print any errors, but we do\n"

# $ECHO "minishell:	|$OUT|"
# # $ECHO "bash: 		|$OUT2|"

# if [ "$OUT" == "$OUT2" ];
# then
# 	$ECHO "Result: ${GREEN}OK${END}"
# else
# 	$ECHO "Result: ${RED}KO${END}"
# fi

# rm -rf res.txt
# rm -rf res2.txt

# $ECHO "----------------------------"

# rm -rf a.out
