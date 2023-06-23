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
	echo "un - run unset tests"
	echo "ex - run export tests"
	echo "exit - exit"
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
	ERROR=$(cat $1)
	ERROR_MINI=${ERROR#*: }
	ERROR_BASH=$(cat $2)
	ERROR_BASH=${ERROR_BASH#*:*: }
	# echo error
	# cat $1
	if [[ $ERROR_MINI == $ERROR_BASH ]]
	then
		# echo yeah
		((OK++))
	else
		# echo nah
		((KO++))
		echo -e "different errors for argument: \n$TEST" >> error_args
	fi
	# if [[ -s $1 && -s $2 ]] || [[ ! -s $1 && ! -s $2 ]]
	# then
	# 	((OK++))
	# else
	# 	((KO++))
	# 	echo -e "different errors for argument: \n$TEST" >> error_args
	# fi
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
		echo -n -e "	🤮${RED}${KO_ALL} TESTS FAILED"
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

test_env(){
	echo "----------------------------------------------------"	
	echo -e "\n	👍${MAGENTA}RUNNING env TESTS${RESET}"
	test_file "testing_files/files/env_test"
	echo "----------------------------------------------------"
}

test_unset(){
	echo "----------------------------------------------------"	
	echo -e "\n	👍${MAGENTA}RUNNING UNSET TESTS${RESET}"
	test_file "testing_files/files/unset_test"
	echo "----------------------------------------------------"
}

test_export(){
	echo "----------------------------------------------------"	
	echo -e "\n	👍${MAGENTA}RUNNING EXPORT TESTS${RESET}"
	test_file "testing_files/files/export_test"
	echo "----------------------------------------------------"
}

test_exit(){
	echo "----------------------------------------------------"	
	echo -e "\n	👍${MAGENTA}RUNNING EXIT TESTS${RESET}"
	test_file "testing_files/files/exit_test"
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
	elif [[ $1 == "env" ]]
	then
		test_env
		read_input
	elif [[ $1 == "un" ]]
	then
		test_unset
		read_input
	elif [[ $1 == "ex" ]]
	then
		test_export
		read_input
	elif [[ $1 == "exit" ]]
	then
		test_exit
		read_input
	elif [[ $1 == "quit" ]]
	then
		return
	else
		read_input
	fi
}

foo=$(make -C .)

main $1	

