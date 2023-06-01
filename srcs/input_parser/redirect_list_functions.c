/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_list_functions.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:19:24 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/01 08:35:20 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_redirect	*make_new_redirect_node(char *name, t_redirect_type type, int fd)
{
	t_redirect	*new_node;

	new_node = malloc(sizeof(t_redirect));
	if (new_node == NULL)
		err_msg(NULL, "parser");
	new_node->fd = fd;
	new_node->name = name;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	add_redirect_back(t_redirect **head, t_redirect *new_redirect)
{
	t_redirect	*temp;

	temp = *head;
	if (temp != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_redirect;
	}
	else
		*head = new_redirect;
}
