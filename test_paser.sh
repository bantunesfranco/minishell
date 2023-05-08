GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'
BOLD='\033[1m'
INCLUDES="-I incs -I libft/incs"
#-g -fsanitize=address
CFLAGS="-Wall -Werror -Wextra"
RL_FLAGS="-L $HOME/.brew/opt/readline/lib -lreadline -I $HOME/.brew/opt/readline/include"
SRC="srcs/parser/main_parser.c srcs/parser/ft_split_args.c srcs/ft_arrdup.c srcs/test_utils.c \
srcs/parser/parser.c"

#!/bin/bash

# compile
rm -rf parse_test
cc $CFLAGS $INCLUDES $RL_FLAGS -o parse_test libft/libft.a $SRC
./parse_test
