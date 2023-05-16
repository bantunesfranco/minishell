/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_error_functions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 11:27:05 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/16 11:41:59 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

/*	writes an error based on what mistake the sintax has, either a token is in the wrong position
	or we have unclosed parenthesis or brackets*/

void	lex_error_function(char *word, int syntax_erorr)
{
	if (syntax_erorr == 1)
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, word, ft_strlen(word));
		write(2, "'\n", 2);
	}
	else
	{
		write(2, "minishell: unexpected newline while looking for matching `", 58);
		write(2, word, 1);
		write(2, "'\n", 2);
	}
}

/*	runs the error function based on the token order and the token where the error was encountered*/

void	token_order_error(t_token *temp, int open_brackets)
{
	if (open_brackets == -1)
		lex_error_function(temp->word, 1);
	else if (temp->type == NEW_LINE || temp->next->type == NEW_LINE)
		lex_error_function("newline", 1);
	else
		lex_error_function(temp->next->word, 1);
}
