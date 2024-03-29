#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
MAGENTA='\033[1;35m'
RESET='\033[0m'
BOLD='\033[1m'


help(){
	echo -e "\n${BOLD}Run with one of the following arguments\n${RESET}"
	echo "all - run all tests"
	echo "echo - run echo tests"
	echo "cd - run cd tests"
	echo "un - run unset tests"
	echo "ex - run export tests"
	echo "exit - run exit tests"
	echo "pip - run pipeline or and tests"
	echo "exp - run expansion tests"
	echo "red - run redirect tests"
	echo "oth - run other (like unset PATH) tests"
	echo "sub - run subshell tests"
	echo "quit - exit"
	echo -e "help - display this message\n"
}

test_output(){
	# LEAKS=$(cat $1 | grep " 0 leaks")
	# if [[ $LEAKS == "" ]]
	# then
	# 	((KO++))
	# 	echo -e "different outputs for argument: \n$TEST\nmini\n`cat $1`\nbash\n`cat $2`\n\n" >> error_args
	# else
	# 	((OK++))
	# fi
	if ! diff -q $1 $2 >/dev/null
	then
		((KO++))
		echo -e "different outputs for argument: \n$TEST\nmini\n`cat $1`\nbash\n`cat $2`\n\n" >> error_args
	else
		((OK++))
	fi
}

test_err(){
	if [[ $HEREDOC == 1 ]]
	then
		# echo huh
		return
	fi
	# echo $TEST
	# # cat $1 | awk '{ if ($0 !~ /exit/) print $0}'
	# echo AWK
	# # awk '!/exit/' $1
	# # cat $1 | awk -v ORS="\n" '{print}'
	# echo SED
	# sed 's/exit\n//g' $1
	NEW=`sed -n '/^exit/!p' $1`
	# echo $NEW
	echo "$NEW" > $1
	# echo BASH
	# cat $2
	# echo DONE
	# cat lol
	# cat lol
	# echo HERE
	# cat $1
	# cat $1
	# echo do
	# echo minishell_err
	# cat $1
	# echo bash_Err
	# cat $2
	# cat $1
	# cat $2
	# echo `cat $1 | grep -v 'exit'`
	if [[ `cat $1` == minishell:* ]]
	then
		ERROR_MINI=$(cut -f2- -d ' ' $1)
		ERROR_BASH=$(cut -f4- -d ' ' $2)
	else
		ERROR_MINI=$(cat $1)
		ERROR_BASH=$(cat $2)
	fi
	# ERROR_MINI=$(cut -f2- -d ' ' $1)
	# ERROR_BASH=$(cut -f4- -d ' ' $2)
	if [[ "$ERROR_MINI" == "$ERROR_BASH" ]]
	then
		((OK++))
	else
		((KO++))
		echo -e "different errors for argument: \n$TEST\nmini\n$ERROR_MINI\nbash\n$ERROR_BASH\n\n" >> error_args
	fi
}

test_code(){
	# echo  minishell $1
	# echo  bash $2
	if [[ $HEREDOC == 1 ]]
	then
		return
	fi
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
		while read -r line
		do
			if [[ $line == "" ]] || [[ $line == \#* ]]
			then
				continue
			elif [[ $line == "HERE" ]]
			then
				HEREDOC=1
				continue
			else
				while [[ $line != "" ]]
				do
					TEST+="$line$NL"
					read -r line
				done
			fi
			# echo "$TEST"
			echo -n "$TEST" | ./minishell 2>err_mini >out_mini
			exit_mini=$?
			echo -n "$TEST" | bash 2>err_bash >out_bash
			exit_bash=$?
			compare out_mini out_bash err_mini err_bash $exit_mini $exit_bash
			TEST=""
			HEREDOC=0
		done < "$FILE"
	if [[ $KO_ALL == 0 ]]
	then
		echo -n -e "	👍${GREEN}TESTS OK"
	else
		echo -n -e "	🤮${RED}${KO_ALL} TESTS KO"
		TEST_FAILED=1
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

test_pipeline_or_and(){
	echo "----------------------------------------------------"	
	echo -e "\n	👍${MAGENTA}RUNNING PIPELINE OR AND TESTS${RESET}"
	test_file "testing_files/files/pipeline_or_and_test"
	echo "----------------------------------------------------"
}

test_expansions(){
	echo "----------------------------------------------------"	
	echo -e "\n	👍${MAGENTA}RUNNING EXPANSION TESTS${RESET}"
	test_file "testing_files/files/expansion_test"
	echo "----------------------------------------------------"
}

test_redirect(){
	touch file
	echo this is a file > file
	echo "----------------------------------------------------"	
	echo -e "\n	👍${MAGENTA}RUNNING REDIRECT TESTS${RESET}"
	test_file "testing_files/files/redirect_test"
	echo "----------------------------------------------------"
	rm file
}

test_other(){
	touch bro.sh
	echo '#!/bin/bash' > bro.sh
	echo "echo hi" >> bro.sh
	chmod +x bro.sh
	touch ls
	echo '#!/bin/bash' > ls
	echo "echo hi" >> ls
	chmod +x ls
	echo "----------------------------------------------------"	
	echo -e "\n	👍${MAGENTA}RUNNING OTHER TESTS${RESET}"
	test_file "testing_files/files/other_test"
	echo "----------------------------------------------------"
	rm ls
	rm bro.sh
}

test_subshells(){
	echo "----------------------------------------------------"	
	echo -e "\n	👍${MAGENTA}RUNNING SUBSHELL TESTS${RESET}"
	test_file "testing_files/files/subshell_test"
	echo "----------------------------------------------------"
}

run_all(){
	test_echo
	test_cd
	test_export
	test_unset
	test_exit
	test_pipeline_or_and
	test_expansions
	test_redirect
	test_other
	test_subshells
	rm -rf hi
	if [[ $TEST_FAILED == "1" ]]
	then
		exit $((TEST_FAILED))
	fi
}

read_input(){
	help
	read option
	main $option
}

main(){
	touch hi
	echo hello > hi
	rm -rf error_args
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
	elif [[ $1 == "pip" ]]
	then
		test_pipeline_or_and
		read_input
	elif [[ $1 == "exp" ]]
	then
		test_expansions
		read_input
	elif [[ $1 == "red" ]]
	then
		test_redirect
		read_input
	elif [[ $1 == "oth" ]]
	then
		test_other
		read_input
	elif [[ $1 == "sub" ]]
	then
		test_subshells
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
rm -rf hi

