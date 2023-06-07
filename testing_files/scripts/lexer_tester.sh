GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'
BOLD='\033[1m'

#!/bin/bash

test_output () {
	if [[ $1 == $2 ]]
	then
		((OK++))
	else
		((KO++))
		echo -e "different errors for argument: \n$TEST\n with output $1\n" >> error_args
	fi
}

test_err () {
	if [[ ! -s $1 ]]
	then
		((OK++))
	else
		((KO++))
		echo -e "different errors for argument: \n$TEST\n with output $1\n" >> error_args
	fi
}


echo "--------------------------------------------------------------------------"
echo -e "\n		${BOLD}${GREEN}Testing lexer${RESET}\n"
make -C testing_files lexer_test > /dev/null
sleep 1
FILE="./testing_files/files/lexer"
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
		OUTPUT=$(./testing_files/lexer_test $line 2>err_mini)
		read -r line
		test_output $OUTPUT $line
		test_err err_mini
		# test_code $exit_mini $exit_bash
	fi
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
rm err_mini

