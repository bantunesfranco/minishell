/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_functions_2.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 10:29:16 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 13:14:48 by jmolenaa      ########   odam.nl         */
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

t_cmd	*find_last_cmd(t_pipeline *cur_pipe)
{
	t_cmd	*temp;

	temp = cur_pipe->first_cmd;
	if (temp != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
	}
	return (temp);
}

t_subshell	*make_new_subshell_struct(t_control_operator type)
{
	t_subshell	*new;

	new = malloc(sizeof(t_subshell));
	if (new == NULL)
		err_msg(NULL, "parser");
	new->pipe_input = 0;
	new->pipe_output = 0;
	new->open_close = type;
	new->input = NULL;
	new->output = NULL;
	return (new);
}
