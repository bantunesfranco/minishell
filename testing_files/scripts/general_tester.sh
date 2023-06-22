GREEN='\033[0;32m'
RED='\033[0;31m'
MAGENTA='\033[1;35m'
RESET='\033[0m'
BOLD='\033[1m'

#!/bin/bash

help(){
	echo -e "\n${BOLD}Run with one of the following arguments\n${RESET}"
	echo "all - run all tests"
	echo "echo - run echo tests"
	echo "cd - run cd tests"
	echo -e "help - display this message\n"
}

test_output(){
	# cat $1
	# cat $2
	if ! diff -q $1 $2 >/dev/null
	then
		((KO++))
		echo -e "different outputs for argument: \n$TEST" >> error_args
	else
		((OK++))
	fi
}

test_err(){
	# echo error
	# cat $1
	# cat $2
	if [[ -s $1 && -s $2 ]] || [[ ! -s $1 && ! -s $2 ]]
	then
		((OK++))
	else
		((KO++))
		echo -e "different errors for argument: \n$TEST" >> error_args
	fi
}

test_code(){
	# echo $1 $2
	if [[ $1 == $2 ]]
	then
		((OK++))
	else
		((KO++))
		echo -e "different error codes for argument: \n$TEST	$1 $2" >> error_args
	fi
}

compare(){
	KO=0
	OK=0
	test_output $1 $2
	test_err $3 $4
	test_code $5 $6
	if [[ $KO == 0 ]]
	then
		((OK_ALL++))
	else
		((KO_ALL++))
	fi
}

test_file(){
	sleep 1
	FILE=$1
	IFS=0
	NL=$'\n'
	KO_ALL=0
	OK_ALL=0
	rm -rf error_args
		while read -r line
		do
			if [[ $line == "" ]] || [[ $line == \#* ]]
			then
				continue
			else
				while [[ $line != "" ]]
				do
					TEST+="$line$NL"
					read -r line
				done
			fi
			# echo $TEST
			echo -n "$TEST" | ./minishell 2>err_mini >out_mini
			exit_mini=$?
			echo -n "$TEST" | bash 2>err_bash >out_bash
			exit_bash=$?
			compare out_mini out_bash err_mini err_bash $exit_mini $exit_bash
			TEST=""
		done < "$FILE"
	if [[ $KO_ALL == 0 ]]
	then
		echo -n -e "	👍${GREEN}TESTS PASSED"
	else
		echo -n -e "	🤮${RED}${KO} TESTS FAILED"
	fi
	total=$((OK_ALL + KO_ALL))
	echo -e " $OK_ALL/$total\n${RESET}"
	rm -f err_*
	rm -f out_*
}

test_echo(){
	echo "----------------------------------------------------"	
	echo -e "\n	👍${MAGENTA}RUNNING ECHO TESTS${RESET}"
	test_file "testing_files/files/echo_test"
	echo "----------------------------------------------------"
}

test_cd(){
	echo "----------------------------------------------------"	
	echo -e "\n	👍${MAGENTA}RUNNING CD TESTS${RESET}"
	test_file "testing_files/files/cd_test"
	echo "----------------------------------------------------"
}

run_all(){
	test_echo
	test_cd
}

read_input(){
	help
	read option
	main $option
}

main(){
	if [[ $1 == "all" ]]
	then
		run_all
	elif [[ $1 == "echo" ]]
	then
		test_echo
		read_input
	elif [[ $1 == "cd" ]]
	then
		test_cd
		read_input
	else
		read_input
	fi
}

foo=$(make -C .)

main $1	

