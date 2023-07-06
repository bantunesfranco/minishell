/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_create_token_word.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 11:05:05 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/04 10:11:26 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parsing.h"
#include "libft.h"

static char	*create_argument_word(char *line, t_par_info *p_info)
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

char	*create_word(char *line, t_token_type token_type, t_par_info *p_info)
{
	char	*new_word;

	if (token_type == CHARACTERS)
		new_word = create_argument_word(line, p_info);
	else
		new_word = ft_strdup(*(p_info->token_array + token_type));
	return (new_word);
}
