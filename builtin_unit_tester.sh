RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
RESET='\033[0m'

INCLUDES="-I incs -I libft/incs"
TESTER_DIR="tests/builtins"

CFLAGS="-Wall -Werror -Wextra"
CFLAGSD="-Wall -Werror -Wextra -g -fsanitize=address"

#!/bin/bash

help_func(){
	echo -e "\n\nall - run all tests"
	echo "cd - run cd tests"
	echo "echo - run echo tests"
	echo "env - run env tests"
	echo "exit - run exit tests"
	echo "export - run export tests"
	echo "pwd - run pwd tests"
	echo "unset - run unset tests"
	echo "help - display this message"
	echo "quit - quit tester"
}

help_arg(){
	echo -e "\n\nall - run all tests"
	echo "cd - run cd tests"
	echo "echo - run echo tests"
	echo "env - run env tests"
	echo "exit - run exit tests"
	echo "export - run export tests"
	echo "pwd - run pwd tests"
	echo "unset - run unset tests"
	echo "help - display this message"
}

readinput(){
	clear
	echo -e "\nWhat mode would you like to run :${RESET}"
	help_func
	echo -e ""
	while [[ $option != "quit" ]]
	do
		read option
		if [[ $option == "all" ]]
		then
			run_all
			help_func
		elif [[ $option == "cd" ]]
		then
			echo -e "\n		${GREEN}Testing cd${RESET}\n"
			test_cd
			help_func
		elif [[ $option == "echo" ]]
		then
			echo -e "\n		${GREEN}Testing echo${RESET}\n"
			test_echo
			help_func
		elif [[ $option == "env" ]]
		then
			echo -e "\n		${GREEN}Testing env${RESET}\n"
			test_env
			help_func
		elif [[ $option == "exit" ]]
		then
			echo -e "\n		${GREEN}Testing exit${RESET}\n"
			test_exit
			help_func
		elif [[ $option == "export" ]]
		then
			echo -e "\n		${GREEN}Testing export${RESET}\n"
			test_export
			help_func
		elif [[ $option == "pwd" ]]
		then
			echo -e "\n		${GREEN}Testing pwd${RESET}\n"
			test_pwd
			help_func
		elif [[ $option == "unset" ]]
		then
			echo -e "\n		${GREEN}Testing unset${RESET}\n"
			test_unset
			help_func
		elif [[ $option == "help" ]]
		then
			help_func
		elif [[ $option == "quit" ]]
		then
			break ;
		else
			echo -e "\nPlease input valid option"
			echo "help - for valid options"
		fi
		echo ""
	done
}

readoption(){
	if [[ $1 == "all" ]]
	then
		run_all
		help_func
	elif [[ $1 == "cd" ]]
	then
		echo -e "\n		${GREEN}Testing cd${RESET}\n"
		test_cd
		help_func
	elif [[ $1 == "echo" ]]
	then
		echo -e "\n		${GREEN}Testing echo${RESET}\n"
		test_echo
		help_func
	elif [[ $1 == "env" ]]
	then
		echo -e "\n		${GREEN}Testing env${RESET}\n"
		test_env
		help_func
	elif [[ $1 == "exit" ]]
	then
		echo -e "\n		${GREEN}Testing exit${RESET}\n"
		test_exit
		help_func
	elif [[ $1 == "export" ]]
	then
		echo -e "\n		${GREEN}Testing export${RESET}\n"
		test_export
		help_func
	elif [[ $1 == "pwd" ]]
	then
		echo -e "\n		${GREEN}Testing pwd${RESET}\n"
		test_pwd
		help_func
	elif [[ $1 == "unset" ]]
	then
		echo -e "\n		${GREEN}Testing unset${RESET}\n"
		test_unset
		help_func
	elif [[ $1 == "help" ]]
	then
		help_func
	elif [[ $1 == "exit" ]]
	then
		break ;
	else
		echo -e "\nPlease input valid option"
		echo "help - for valid options"
	fi
	echo ""
}

test_cd () {
	$(bash $TESTER_DIR/cd/test_cd.sh > $TESTER_DIR/cd_log 2>> $TESTER_DIR/err_log)
	OK=$(grep "Result:" < $TESTER_DIR/cd_log | grep -c "OK")
	KO=$(grep "Result:" < $TESTER_DIR/cd_log | grep -c "KO")
	TESTS=$(($OK + $KO))

	if [[ $KO == 0 ]]
	then
		echo -e "${GREEN}OK - Passed $OK/$TESTS tests${RESET}"
	else
		echo -e "${RED}KO - Failed $KO/$TESTS tests${RESET}"
	fi
}

main () {
	if [[ $# == 0 ]]
	then
		echo "no input"
		readinput
	else
		echo $1
		runoption $1
	fi
}

main $1