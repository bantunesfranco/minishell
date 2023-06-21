/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_redirect_state.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 14:25:59 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/21 11:43:29 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

void	add_redirect_to_cmd(t_pipeline *curr_pipeline, t_redirect *new_redirect)
{
	t_cmd	*current_cmd;

	current_cmd = find_curr_cmd(curr_pipeline);
	if (current_cmd == NULL)
	{
		current_cmd = make_new_simple_cmd();
		curr_pipeline->first_cmd = current_cmd;
	}
	if (new_redirect->type == HEREDOC || new_redirect->type == INPUT)
		add_redirect_back(&(current_cmd->input), new_redirect);
	else
		add_redirect_back(&(current_cmd->output), new_redirect);
}

t_token	*redirection_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token)
{
	t_redirect	*new_redirect;
	t_token		*next_token;
	
	new_redirect = make_new_redirect_node(temp->next->word, temp->type - 5, -1);
	new_redirect->str = temp->str;
	add_redirect_to_cmd(curr_pipeline, new_redirect);
	next_token = temp->next->next;
	remove_token(first_token, temp->next);
	remove_token(first_token, temp);
	return (next_token);
}