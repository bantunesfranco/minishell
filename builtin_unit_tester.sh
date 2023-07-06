RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
RESET='\033[0m'

INCLUDES="-I incs -I libft/incs"
TESTER_DIR="testing_files/builtins"

CFLAGS="-Wall -Werror -Wextra"
CFLAGSD="-Wall -Werror -Wextra -g -fsanitize=address"

#!/bin/bash

rm -rf $TESTER_DIR/logs
mkdir $TESTER_DIR/logs

help_func(){
	echo -e "\nall - run all tests"
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
	echo -e "\nall - run all tests"
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
	echo -e "\nWhich test would you like to run :"
	help_func
	echo -e ""
	while [[ $option != "quit" ]]
	do
		read option
		if [[ $option == "all" ]]
		then
			run_all
		elif [[ $option =~ ^(cd|echo|env|exit|export|pwd|unset)$ ]]
		then
			echo -en "\n---------------------------------------------"
			echo -e "\n\t\t${BLUE}Testing $option${RESET}\n"
			test_$option
			echo -e "\n---------------------------------------------"
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
		echo -e "Which test would you like to run :"
	done
}

runoption(){
	if [[ $1 == "all" ]]
	then
		run_all
	elif [[ $1 =~ ^(cd|echo|env|exit|export|pwd|unset)$ ]]
	then
		echo -en "\n---------------------------------------------"
		echo -e "\n\t\t${BLUE}Testing $1${RESET}\n"
		test_$1
		echo -e "\n---------------------------------------------"
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
	$(bash $TESTER_DIR/cd/test_cd.sh > $TESTER_DIR/logs/cd_log 2>> $TESTER_DIR/logs/err_log)
	$(echo "" >> $TESTER_DIR/logs/err_log)
	OK=$(grep "Result:" < $TESTER_DIR/logs/cd_log | grep -c "OK")
	KO=$(grep "Result:" < $TESTER_DIR/logs/cd_log | grep -c "KO")
	TESTS=$(($OK + $KO))

	if [[ $KO == 0 ]]
	then
		echo -en "\t${GREEN}OK - Passed $OK/$TESTS tests${RESET}"
	else
		echo -en "\t${RED}KO - Failed $KO/$TESTS tests${RESET}"
		echo -e "\n" && exit 1
	fi
}

test_echo () {
	$(bash $TESTER_DIR/echo/test_echo.sh > $TESTER_DIR/logs/echo_log 2>> $TESTER_DIR/logs/err_log)
	$(echo "" >> $TESTER_DIR/logs/err_log)
	OK=$(grep "Result:" < $TESTER_DIR/logs/echo_log | grep -c "OK")
	KO=$(grep "Result:" < $TESTER_DIR/logs/echo_log | grep -c "KO")
	TESTS=$(($OK + $KO))

	if [[ $KO == 0 ]]
	then
		echo -en "\t${GREEN}OK - Passed $OK/$TESTS tests${RESET}"
	else
		echo -en "\t${RED}KO - Failed $KO/$TESTS tests${RESET}"
		echo -e "\n" && exit 1
	fi
}

test_env () {
	$(bash $TESTER_DIR/env/test_env.sh > $TESTER_DIR/logs/env_log 2>> $TESTER_DIR/logs/err_log)
	$(echo "" >> $TESTER_DIR/logs/err_log)
	OK=$(grep "Result:" < $TESTER_DIR/logs/env_log | grep -c "OK")
	KO=$(grep "Result:" < $TESTER_DIR/logs/env_log | grep -c "KO")
	TESTS=$(($OK + $KO))

	if [[ $KO == 0 ]]
	then
		echo -en "\t${GREEN}OK - Passed $OK/$TESTS tests${RESET}"
	else
		echo -en "\t${RED}KO - Failed $KO/$TESTS tests${RESET}"
		echo -e "\n" && exit 1
	fi
}

test_exit () {
	$(bash $TESTER_DIR/exit/test_exit.sh > $TESTER_DIR/logs/exit_log 2>> $TESTER_DIR/logs/err_log)
	$(echo "" >> $TESTER_DIR/logs/err_log)
	OK=$(grep "Result:" < $TESTER_DIR/logs/exit_log | grep -c "OK")
	KO=$(grep "Result:" < $TESTER_DIR/logs/exit_log | grep -c "KO")
	TESTS=$(($OK + $KO))

	if [[ $KO == 0 ]]
	then
		echo -en "\t${GREEN}OK - Passed $OK/$TESTS tests${RESET}"
	else
		echo -en "\t${RED}KO - Failed $KO/$TESTS tests${RESET}"
		echo -e "\n" && exit 1
	fi
}

test_export () {
	$(bash $TESTER_DIR/export/test_export.sh > $TESTER_DIR/logs/export_log 2>> $TESTER_DIR/logs/err_log)
	$(echo "" >> $TESTER_DIR/logs/err_log)
	OK=$(grep "Result:" < $TESTER_DIR/logs/export_log | grep -c "OK")
	KO=$(grep "Result:" < $TESTER_DIR/logs/export_log | grep -c "KO")
	TESTS=$(($OK + $KO))

	if [[ $KO == 0 ]]
	then
		echo -en "\t${GREEN}OK - Passed $OK/$TESTS tests${RESET}"
	else
		echo -en "\t${RED}KO - Failed $KO/$TESTS tests${RESET}"
		echo -e "\n" && exit 1
	fi
}

test_pwd () {
	$(bash $TESTER_DIR/pwd/test_pwd.sh > $TESTER_DIR/logs/pwd_log 2>> $TESTER_DIR/logs/err_log)
	$(echo "" >> $TESTER_DIR/logs/err_log)
	OK=$(grep "Result:" < $TESTER_DIR/logs/pwd_log | grep -c "OK")
	KO=$(grep "Result:" < $TESTER_DIR/logs/pwd_log | grep -c "KO")
	TESTS=$(($OK + $KO))

	if [[ $KO == 0 ]]
	then
		echo -en "\t${GREEN}OK - Passed $OK/$TESTS tests${RESET}"
	else
		echo -en "\t${RED}KO - Failed $KO/$TESTS tests${RESET}"
		echo -e "\n" && exit 1
	fi
}

test_unset () {
	$(bash $TESTER_DIR/unset/test_unset.sh > $TESTER_DIR/logs/unset_log 2>> $TESTER_DIR/logs/err_log)
	$(echo "" >> $TESTER_DIR/logs/err_log)
	OK=$(grep "Result:" < $TESTER_DIR/logs/unset_log | grep -c "OK")
	KO=$(grep "Result:" < $TESTER_DIR/logs/unset_log | grep -c "KO")
	TESTS=$(($OK + $KO))

	if [[ $KO == 0 ]]
	then
		echo -en "\t${GREEN}OK - Passed $OK/$TESTS tests${RESET}"
	else
		echo -en "\t${RED}KO - Failed $KO/$TESTS tests${RESET}"
		echo -e "\n" && exit 1
	fi
}

run_all () {
	OPTIONS=("cd" "echo" "env" "exit" "export" "pwd" "unset")
	for option in ${OPTIONS[@]}
	do
		echo -en "\n---------------------------------------------"
		echo -e "\n\t\t${BLUE}Testing $option${RESET}\n"
		test_$option
	done
	echo -e "\n---------------------------------------------"
}


main () {
	if [[ $# == 0 ]]
	then
		readinput
	else
		runoption $1
	fi
}

main $1