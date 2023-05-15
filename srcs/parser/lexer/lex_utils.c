/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 19:56:00 by janmolenaar   #+#    #+#                 */
/*   Updated: 2023/05/15 11:41:28 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

/*	these functions are kind of self explanatory*/

void	add_new_token_to_back(t_token **first_token, t_token *new_token)
{
	t_token	*temp;

	temp = *first_token;
	if (temp == NULL)
		*first_token = new_token;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_token;
		new_token->prev = temp;
	}
}

t_token	*make_new_token(char *word, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->word = word;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/*	skips the quotes by storing which ones we encountered in c and then looping till the next c or \0 */

size_t	skip_quotes(char *line, size_t i)
{
	char	c;

	c = *(line + i);
	i++;
	while (*(line + i) != c && *(line + i) != '\0')
		i++;
	return (i);
}

/*	similar to the function from creating words*/

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
