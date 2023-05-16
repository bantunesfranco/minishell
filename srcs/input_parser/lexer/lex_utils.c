/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 19:56:00 by janmolenaar   #+#    #+#                 */
/*   Updated: 2023/05/16 14:19:16 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

/*	these functions are kind of self explanatory*/

void	free_token_list(t_token *first_token)
{
	t_token	*temp;

	while (first_token != NULL)
	{
		temp = first_token;
		first_token = first_token->next;
		free(temp->word);
		free(temp);
	}
}

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
