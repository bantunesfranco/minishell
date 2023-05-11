/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_list_func.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 19:56:00 by janmolenaar   #+#    #+#                 */
/*   Updated: 2023/05/10 19:56:33 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "parsing_structs.h"
#include <stdlib.h>

void	add_token_to_back(t_token **first_token, t_token *new_token)
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
