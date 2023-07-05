/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 14:24:01 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 13:22:47 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	add_standard_in_out_nodes(t_cmd *current_cmd)
{
	if (current_cmd->input == NULL)
		current_cmd->input = make_new_redirect_node(NULL, INPUT, 0);
	if (current_cmd->output == NULL)
		current_cmd->output = make_new_redirect_node(NULL, OUTPUT, 1);
}

void	close_cmd(t_token *temp, t_pipeline *cur_pipe, t_token **head)
{
	t_cmd	*current_cmd;

	current_cmd = find_last_cmd(cur_pipe);
	if (current_cmd == NULL)
	{
		current_cmd = make_new_simple_cmd();
		cur_pipe->first_cmd = current_cmd;
	}
	current_cmd->cmd = create_cmd_array(temp, *head);
	add_standard_in_out_nodes(current_cmd);
	remove_tokens(temp, head);
}
