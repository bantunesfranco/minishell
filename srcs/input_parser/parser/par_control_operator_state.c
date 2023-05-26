/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_control_operator_state.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 15:30:37 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/26 19:36:24 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

void	add_simple_cmd(t_pipeline *curr_pipeline)
{
	t_cmd	*new_cmd;

	new_cmd = make_new_simple_cmd();
	if (new_cmd == NULL)
		exit (1);								//malloc failure
	add_simple_cmd_back(&(curr_pipeline->first_cmd), new_cmd);
}

void	add_pipeline(t_pipeline *curr_pipeline)
{
	t_pipeline	*new_pipeline;

	new_pipeline = make_new_pipeline();
	if (new_pipeline == NULL)
		exit (1);								//malloc failure
	curr_pipeline->next = new_pipeline;
}

static void	remove_tokens(t_token *temp, t_token **first_token)
{
	t_token	*temp2;

	temp2 = *first_token;
	while (temp2 != temp)
	{
		temp2 = temp2->next;
		remove_token(first_token, temp2->prev);
	}
	remove_token(first_token, temp);
}

t_token	*control_operator_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token)
{
	t_token	*next_token;
	// t_cmd	*temp_cmd;

	close_simple_cmd(temp, curr_pipeline, *first_token);
	// temp_cmd = find_curr_cmd(curr_pipeline);
	// print_array(temp_cmd->cmd);
	if (temp->type == PIPE && temp->next->token_group != PARENTHESIS)
	{
		printf("hi\n");
		add_simple_cmd(curr_pipeline);
	}
	else
		add_pipeline(curr_pipeline);
	next_token = temp->next;
	remove_tokens(temp, first_token);
	return (next_token);
}
