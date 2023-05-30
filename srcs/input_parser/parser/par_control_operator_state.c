/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_control_operator_state.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 15:30:37 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/29 14:38:40 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static void	add_simple_cmd(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token)
{
	t_cmd	*new_cmd;

	close_simple_cmd(temp, curr_pipeline, first_token);
	new_cmd = make_new_simple_cmd();
	add_simple_cmd_back(&(curr_pipeline->first_cmd), new_cmd);
}

static void	add_pipeline(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token)
{
	t_pipeline	*new_pipeline;

	close_simple_cmd(temp, curr_pipeline, first_token);
	curr_pipeline->next_control_operator = (t_control_operator)temp->type;
	new_pipeline = make_new_pipeline((t_control_operator)temp->type);
	new_pipeline->prev = curr_pipeline;
	curr_pipeline->next = new_pipeline;
}

t_token	*control_operator_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token)
{
	t_token	*next_token;

	if (temp->type == PIPE && temp->next->token_group != PARENTHESIS)
		add_simple_cmd(temp, curr_pipeline, first_token);
	else
		add_pipeline(temp, curr_pipeline, first_token);
	next_token = temp->next;
	remove_token(first_token, temp);
	return (next_token);
}
