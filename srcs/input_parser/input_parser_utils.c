/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parser_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 19:38:46 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 13:47:52 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

size_t	skip_quotes(char *line, size_t i)
{
	char	c;

	c = *(line + i);
	i++;
	while (*(line + i) != c && *(line + i) != '\0')
		i++;
	return (i);
}

bool	are_quotes_closed(char *word)
{
	size_t	i;
	char	c;

	i = 0;
	while (*(word + i) != '\0')
	{
		if (*(word + i) == '\'' || *(word + i) == '"')
		{
			c = *(word + i);
			i = skip_quotes(word, i);
		}
		if (*(word + i) == '\0')
		{
			lex_error_function(&c, 2);
			return (false);
		}
		i++;
	}
	return (true);
}

static void	setup_token_array(char *token_array[13])
{
	token_array[0] = "||";
	token_array[1] = "|";
	token_array[2] = "&&";
	token_array[3] = "(";
	token_array[4] = ")";
	token_array[5] = "<<";
	token_array[6] = "<";
	token_array[7] = ">>";
	token_array[8] = ">";
	token_array[9] = " ";
	token_array[10] = "\t";
	token_array[11] = "\n";
	token_array[12] = NULL;
}

static void	setup_meta_characters(char meta_characters[8])
{
	meta_characters[0] = '|';
	meta_characters[1] = '(';
	meta_characters[2] = ')';
	meta_characters[3] = '<';
	meta_characters[4] = '>';
	meta_characters[5] = ' ';
	meta_characters[6] = '\t';
	meta_characters[7] = '\n';
	meta_characters[8] = '\0';
}

void	init_struct(t_par_info *p_info)
{
	setup_meta_characters(p_info->metacharacters);
	setup_token_array(p_info->token_array);
	p_info->syntax_error = 0;
	p_info->error_token = NULL;
}
