GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'
BOLD='\033[1m'

#!/bin/bash

# functions comparing output, error and error code

test_output(){
	if ! diff -q $1 $2 >/dev/null
	then
		((KO++))
		echo -e "different outputs for argument: \n$TEST" >> error_args
	else
		((OK++))
	fi
}

test_err(){
	if [[ -s $1 && -s $2 ]] || [[ ! -s $1 && ! -s $2 ]]
	then
		((OK++))
	else
		((KO++))
		echo -e "different errors for argument: \n$TEST" >> error_args
	fi
}

test_code(){
	if [[ $1 == $2 ]]
	then
		echo -e "${GREEN}OK${RESET}"
	else
		echo -e "${RED}KO${RESET}"
	fi
}

# script

echo "--------------------------------------------------------------------------"
echo -e "\n		${BOLD}${GREEN}Testing syntax errors${RESET}\n"
make -C testing_files syntax_test > /dev/null
sleep 1
FILE="./testing_files/files/syntax_errors"
IFS=0
NL=$'\n'
KO=0
OK=0
while read -r line
do
	if [[ $line == "" ]]
	then
		continue
	else
		while [[ $line != "" ]]
		do
			TEST+="$line$NL"
			read -r line
		done
	fi
	./testing_files/syntax_test $TEST 2>err_mini >out_mini
	exit_mini=$?
	echo -n "$TEST" | bash 2>err_bash >out_bash
	exit_bash=$?
	test_output out_mini out_bash
	test_err err_mini err_bash
	TEST=""
done < "$FILE"
if [[ $KO == 0 ]]
then
	echo -n -e "\n		👍${GREEN}TESTS PASSED"
else
	echo -n -e "\n		🤮${RED}${KO} TESTS FAILED"
fi
total=$((OK + KO))
echo -e " $OK/$total\n${RESET}"
echo "--------------------------------------------------------------------------"
rm -f err_*
rm -f out_*
