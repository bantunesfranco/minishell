/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_marking.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 08:37:07 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/19 14:38:58 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "libft.h"
#include "parsing.h"

size_t	skip_quotes_if_neccesarry(size_t i, t_quote_mark **head)
{
	if (*(head) != NULL && (*head)->word_index == i)
	{
		i = (*head)->next->word_index;
		*head = (*head)->next->next;
	}
	return (i);
}

void	free_quote_list(t_quote_mark *head)
{
	t_quote_mark	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

t_quote_mark	*make_new_quote_node(size_t i)
{
	t_quote_mark	*new;

	new = malloc(sizeof(t_quote_mark));
	if (new == NULL)
		err_msg(NULL, "expander");
	new->array_index = 0;
	new->word_index_2 = i;
	new->word_index = i;
	new->next = NULL;
	return (new);
}

void	add_quote_back(t_quote_mark **head, t_quote_mark *new)
{
	t_quote_mark	*temp;

	temp = *head;
	if (temp == NULL)
		*head = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

size_t	handle_quotes(char *word, size_t i, t_quote_mark **head)
{
	t_quote_mark	*new;

	new = make_new_quote_node(i);
	add_quote_back(head, new);
	if (*(word + i) == '"')
		return (i);
	i = skip_quotes(word, i);
	new = make_new_quote_node(i);
	add_quote_back(head, new);
	return (i);
}
