/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_cmd_list_functions.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 10:29:16 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/01 15:22:02 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

t_cmd	*make_new_simple_cmd(void)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (new_node == NULL)
		err_msg(NULL, "parser");
	new_node->cmd = NULL;
	new_node->path = NULL;
	new_node->builtin = NULL;
	new_node->cmd_count = 0;
	new_node->input = NULL;
	new_node->output = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_simple_cmd_back(t_cmd **head, t_cmd *new_simple_cmd)
{
	t_cmd	*temp;

	temp = *head;
	if (temp != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_simple_cmd;
		new_simple_cmd->prev = temp;
	}
	else
		*head = new_simple_cmd;
}
