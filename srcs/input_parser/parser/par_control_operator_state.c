/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_control_operator_state.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 15:30:37 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 13:27:06 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_simple_cmd(t_token *temp, t_pipeline *cur_pipe, t_token **head)
{
	t_cmd	*new_cmd;

	close_cmd(temp, cur_pipe, head);
	new_cmd = make_new_simple_cmd();
	add_simple_cmd_back(&(cur_pipe->first_cmd), new_cmd);
}

void	add_pipeline(t_token *temp, t_pipeline *cur_pipe, t_token **head)
{
	t_pipeline	*new_pipeline;

	close_cmd(temp, cur_pipe, head);
	cur_pipe->next_control_operator = (t_control_operator)temp->type;
	new_pipeline = make_new_pipeline((t_control_operator)temp->type);
	cur_pipe->next = new_pipeline;
}

t_token	*ctrl_op_st(t_token *temp, t_pipeline *cur_pipe, t_token **head)
{
	t_token	*next_token;

	if (temp->type == PIPE && temp->next->token_group != PARENTHESIS \
		&& cur_pipe->prev_control_operator != CLOSE)
		add_simple_cmd(temp, cur_pipe, head);
	else
		add_pipeline(temp, cur_pipe, head);
	next_token = temp->next;
	remove_token(head, temp);
	return (next_token);
}
