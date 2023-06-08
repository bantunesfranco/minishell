/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_create_token_word.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 11:05:05 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/08 19:41:00 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parsing.h"
#include "libft.h"

/*	loops through string until it encounters one of the metacharacters
	& is done separately since we're treating a single & as a normal character but a && separates words
	if we encounter a quote we skip over that part
	check for NULL after quote skip since we might encounter ucnlosed quotes
	returns the substr of the word as an allocated string */

static char	*create_argument_word(char *line, t_parsing_info *p_info)
{
	size_t	i;

	i = 0;
	while (ft_strchr(p_info->metacharacters, *(line + i)) == NULL)
	{
		if (*(line + i) == '&' && *(line + i + 1) == '&')
			break ;
		if (*(line + i) == '\'' || *(line + i) == '"')
			i = skip_quotes(line, i);
		if (*(line + i) == '\0')
			break ;
		i++;
	}
	return (ft_substr(line, 0, i));
}

/*	mallocs and copies word based on token type
	if we have a word will substr the word until it encounters a metacharacter
	anything else it duplicates a string from our token array, a PIPE_PIPE token will be dupped to "||" f.e.
	returns malloced word */

char	*create_word(char *line, t_token_type new_token_type, t_parsing_info *p_info)
{
	char	*new_word;

	if (new_token_type == CHARACTERS)
		new_word = create_argument_word(line, p_info);
	else
		new_word = ft_strdup(*(p_info->token_array + new_token_type));
	return(new_word);
}
