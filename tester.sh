#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'
BOLD='\033[1m'


help_arg(){
	echo -e "\n${BOLD}Run ./tester with one of the following arguments\n${RESET}"
	echo -e "run - start minishell"
	echo "unit [option]- run one of the unit tests with an option:"
	echo "	all - run all unit tests"
	echo "	sy - run lexer tests"
	echo "	le - run syntax error tests"
	echo "gen - run general module"
	echo "all - run all tests"
	echo "clean - cleanup files"
	echo "help - display this message"
}

help_unit_arg(){
	echo -e "\n\n${BOLD}Please input one of the following options${RESET}"
	echo -e "\n\nall - run all unit tests"
	echo "sy - run syntax error tests"
	echo "le - run lexer tests"
	echo "help - display this message"
	echo "exit - to stop the tester"
}

unit_test(){
	if [[ $1 == "sy" ]]
	then
		test_syntax
	elif [[ $1 == "le" ]]
	then
		test_lexer
	elif [[ $1 == "all" ]]
	then
		test_all_unit
		return
	elif [[ $1 == "exit" ]]
	then
		return
	else
		help_unit_arg
	fi
	read option
	unit_test $option
}

runoption(){
	if [[ $1 == "run" ]]
	then
		run_minishell
	elif [[ $1 == "gen" ]]
	then
		general_test $2
	elif [[ $1 == "unit" ]]
	then
		unit_test $2
	elif [[ $1 == "all" ]]
	then
		run_all_tests $2
	elif [[ $1 == "clean" ]]
	then
		make -s -C testing_files fclean
	else
		help_arg
	fi
	echo ""
}

main () {
	runoption $1 $2 $3 $4
}

general_test() {
	rm -rf error_args
	./testing_files/scripts/general_tester.sh $1
	EXIT_CODE=$?
	exit $((EXIT_CODE))
}

run_minishell () {
	foo=$(make -C .)
	./minishell
}

test_if_passed(){
	check=$(echo $1 | grep "TESTS PASSED")
	if [ -z "$check" ]
	then
		BAD=1
		echo -e ":${RED}			KO ${RESET}"
	else
		echo -e ":${GREEN}			OK ${RESET}"
	fi
}

test_if_passed_all(){
	check=$(echo -e $1 | grep KO)
	if [ -z "$check" ]
	then
		echo -e ":${GREEN}			OK${RESET}"
	else
		BAD=1
		echo -e ":${RED}			KO${RESET}"
	fi
}

run_all_tests() {
	BAD=0
	rm -rf error_args
	echo -n -e "\nUnit tests"
	ARG=$(test_all_unit)
	test_if_passed_all "$ARG"
	echo -n -e "\nGeneral tests"
	ARG=$(general_test all)
	test_if_passed_all "$ARG"
	exit $BAD
}

test_all_unit() {
	BAD=0
	rm -rf error_args
	echo -n -e "\nTesting syntax errors"
	ARG=$(./testing_files/scripts/syntax_error.sh)
	test_if_passed "$ARG"
	echo -n "Testing lexer	"
	ARG=$(./testing_files/scripts/lexer_tester.sh)
	test_if_passed "$ARG"
	exit $BAD
}

test_syntax () {
	rm -rf error_args
	./testing_files/scripts/syntax_error.sh
}

test_lexer () {
	rm -rf error_args
	./testing_files/scripts/lexer_tester.sh
}

main $1 $2
