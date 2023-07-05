/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_functions_1.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 10:25:22 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 13:30:53 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

t_pipeline	*make_new_pipeline(t_control_operator type)
{
	t_pipeline	*new_node;

	new_node = malloc(sizeof(t_pipeline));
	if (new_node == NULL)
		err_msg(NULL, "parser");
	new_node->next_control_operator = 0;
	new_node->prev_control_operator = type;
	new_node->subshell = NULL;
	new_node->first_cmd = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_pipeline	*find_last_pipeline(t_pipeline *first_pipeline)
{
	t_pipeline	*temp;

	temp = first_pipeline;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

t_redirect	*make_new_redirect_node(char *name, t_redirect_type type, int fd)
{
	t_redirect	*new_node;

	new_node = malloc(sizeof(t_redirect));
	if (new_node == NULL)
		err_msg(NULL, "parser");
	new_node->fd = fd;
	new_node->name = name;
	new_node->type = type;
	new_node->str = NULL;
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
