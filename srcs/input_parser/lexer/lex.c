/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 10:37:32 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/16 12:02:57 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*	The lexer will go through our line and separate it into tokens that will then be used in out parser to create the cmd list
	First it creates the list of tokens, it will create nodes with the type of token and the part of the line that is there
	Then we assign the token groups which groups tokens according to the function they perform
	At the end it validates the syntax of the input*/

void	lexer(char *line, t_parsing_info *p_info, t_token **first_token)
{
	create_token_list(line, p_info, first_token); // will create a malloced list of tokens with malloced words in them
	assign_token_groups(*first_token);
	validate_syntax(*first_token, p_info);
	if (p_info->syntax_error == 0) // remove later
		printf("no error\n");
}
