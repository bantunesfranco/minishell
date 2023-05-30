/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list_functions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 19:56:00 by janmolenaar   #+#    #+#                 */
/*   Updated: 2023/05/29 14:17:09 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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
		err_msg(NULL, "parser");
	new->word = word;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	remove_token(t_token **first_token, t_token *node_to_delete)
{
	t_token	*temp;

	temp = *first_token;
	while (temp != node_to_delete)
		temp = temp->next;
	if (temp == *first_token)
	{
		*first_token = temp->next;
		if (temp->next != NULL)
			temp->next->prev = NULL;
	}
	else if (temp->next != NULL)
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	if (temp->token_group != WORD)
		free(temp->word);
	free(temp);
}

void	remove_tokens(t_token *temp, t_token **first_token)
{
	t_token	*temp2;

	temp2 = *first_token;
	while (temp2 != temp)
	{
		temp2 = temp2->next;
		remove_token(first_token, temp2->prev);
	}
}
