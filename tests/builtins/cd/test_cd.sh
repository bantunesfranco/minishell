RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
END='\033[0m'

INCLUDES="-I incs -I libft/incs"
SRCS="tests/builtins/cd/cd_main.c srcs/builtins/cd.c srcs/builtins/pwd.c \
srcs/builtins/export2.c srcs/init/ft_arrdup.c srcs/utils.c srcs/error.c libft/libft.a"

CFLAGS="-Wall -Werror -Wextra -g -fsanitize=address"
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

CWD=$(pwd)
export PWD=$CWD

mkdir $PWD/test_home
EC=$(echo $?)
if [ $EC != "0" ];
then
	exit 1
fi

$ECHO "\n	${CYAN}CD TESTER${END}\n----------------------------"

$ECHO "	${MAGENTA}TO STDOUT${END}\n----------------------------"
$ECHO "${BLUE}Test 1 - 'cd'\n${END}"

TEMP=$HOME
export HOME=$PWD/test_home

OUT=$(./a.out "pwd" "cd")
OUT2=$(pwd && cd && echo -n "                 " && pwd)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

export HOME=$TEMP

$ECHO "----------------------------"

$ECHO "${BLUE}Test 2 - 'cd --' with HOME\n${END}"

TEMP=$HOME
export HOME=$PWD/test_home

OUT=$(./a.out "pwd" "cd --")
OUT2=$(pwd && cd -- && echo -n "                 " && pwd)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

rm -rf $PWD/test_home
export HOME=$TEMP

$ECHO "----------------------------"

$ECHO "${BLUE}Test 3 - 'cd -' with OLDPWD\n${END}"

TEMP=$OLDPWD
export OLDPWD="$PWD/tests/builtins/cd"

OUT=$(./a.out "pwd" "cd -")
OUT2=$(pwd && cd - && echo -n "                 " && pwd)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

export OLDPWD=$TEMP

$ECHO "----------------------------"

$ECHO "${BLUE}Test 4 - 'cd .'\n${END}"
OUT=$(./a.out "pwd" "cd .")
OUT2=$(pwd && cd . && echo -n "                 " && pwd)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 5 - 'cd ..'\n${END}"
OUT=$(./a.out "pwd" "cd ..")
OUT2=$(pwd && cd .. && echo -n "                 " && pwd)

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
OUT=$(./a.out "pwd" "cd /")
OUT2=$(pwd && cd / && echo -n "                 " && pwd)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 7 - 'cd incs'\n${END}"
OUT=$(./a.out "pwd" "cd incs")
OUT2=$(pwd && cd incs && echo -n "                 " && pwd)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 8 - 'cd srcs/builtins'\n${END}"
OUT=$(./a.out "pwd" "cd srcs/builtins")
OUT2=$(pwd && cd srcs/builtins && echo -n "                 " && pwd)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

$ECHO "----------------------------"

$ECHO "${BLUE}Test 9 - 'cd ..' with no OLDPWD\n${END}"

TEMP=$OLDPWD
unset OLDPWD

env | grep OLDPWD=

OUT=$(./a.out "pwd" "cd ..")
OUT2=$(pwd && cd .. && echo -n "                 " && pwd)

$ECHO "minishell:	|$OUT|"
$ECHO "bash: 		|$OUT2|"

if [ "$OUT" == "$OUT2" ];
then
	$ECHO "Result: ${GREEN}OK${END}"
else
	$ECHO "Result: ${RED}KO${END}"
fi

export OLDPWD=$TEMP

$ECHO "----------------------------"

####################################
#          REDIRECTIONS            #
####################################

$ECHO "	${MAGENTA}TO TXT FILE${END}\n----------------------------"

$ECHO "${BLUE}Test 1 - 'cd -'\n${END}"

TEMP=$OLDPWD
export OLDPWD=$PWD/tests/builtins/cd

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "pwd" "cd -" res.txt > /dev/null && < res.txt cat)
OUT2=$( (cd -) > res2.txt && < res2.txt cat)

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

export OLDPWD=$TEMP

$ECHO "----------------------------"

####################################
#         ERROR HANDELING          #
####################################

$ECHO "      ${MAGENTA}ERROR HANDELING${END}\n----------------------------"

$ECHO "${BLUE}Test 1 - 'cd' with no HOME\n${END}"

TEMP=$HOME
unset HOME

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "pwd" "cd" > /dev/null 2> res.txt; \
< res.txt cat | awk -F ': ' ' {print $NF}')
OUT2=$( (cd) > /dev/null 2> res2.txt; \
< res2.txt cat | awk -F ': ' ' {print $NF}')

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

export HOME=$TEMP

$ECHO "----------------------------"

$ECHO "${BLUE}Test 2 - 'cd --' with no HOME\n${END}"

TEMP=$HOME
unset HOME

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "pwd" "cd --" > /dev/null 2> res.txt; \
< res.txt cat | awk -F ': ' ' {print $NF}')
OUT2=$( (cd --) > /dev/null 2> res2.txt; \
< res2.txt cat | awk -F ': ' ' {print $NF}')

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

export HOME=$TEMP

$ECHO "----------------------------"

$ECHO "${BLUE}Test 3 - 'cd -' no OLDPWD\n${END}"

TEMP=$OLDPWD
unset OLDPWD

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "pwd" "cd -" > /dev/null 2> res.txt; \
< res.txt cat | awk -F ': ' ' {print $NF}')
OUT2=$( (cd -) > /dev/null 2> res2.txt; \
< res2.txt cat | awk -F ': ' ' {print $NF}')

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

export OLDPWD=$TEMP

$ECHO "----------------------------"

$ECHO "${BLUE}Test 4 - 'cd' with nonexistant path\n${END}"

mkdir $PWD/nonexistantpath
EC=$(echo $?)
if [ $EC != "0" ];
then
	exit 1
fi
rm -rf nonexistantpath

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "pwd" "cd nonexistantpath" > /dev/null 2> res.txt; \
< res.txt cat | awk -F ': ' ' {print $NF}')
OUT2=$( (cd nonexistantpath) > /dev/null 2> res2.txt; \
< res2.txt cat | awk -F ': ' ' {print $NF}')

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

$ECHO "${BLUE}Test 5 - 'cd' with too many args\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

OUT=$(./a.out "pwd" "cd .. hello" > /dev/null 2> res.txt; \
< res.txt cat | awk -F ': ' ' {print $NF}')
OUT2=$( (cd .. hello) > /dev/null 2> res2.txt; \
< res2.txt cat | awk -F ': ' ' {print $NF}')

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

$ECHO "${BLUE}Test 6 - 'closed stdout'\n${END}"

touch res.txt && chmod 777 res.txt
touch res2.txt && chmod 777 res2.txt

TEMP=$OLDPWD
export OLDPWD="$PWD/tests/builtins/cd"

OUT=$(exec 3>&1; exec 1<&-; ./a.out "pwd" "cd -" 2> res.txt; exec 1>&3;\
< res.txt cat | awk -F ': ' 'FNR == 2  {print $NF}')
OUT2="Bad file descriptor"

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

export OLDPWD=$TEMP

$ECHO "----------------------------"

rm -rf a.out