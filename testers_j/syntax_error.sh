#!/bin/bash

FILE="./testers_j/files/syntax_errors"
IFS=0
i=1
line_count=0
NL=$'\n'

	while read -r line
	do
		# echo $line
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
		echo $TEST
		# echo -e 'lol\n'
		echo -n "$TEST" | ./minishell
		TEST=""
	done < "$FILE"



# echo uu | ./minishell
# echo hi '
# cat | || echo hi

# cat | && echo hi

# cat | | echo hi

# cat || | echo hi

# cat || && echo hi

# cat || || echo hi

# cat && | echo hi

# cat && || echo hi

# cat && && echo hi
