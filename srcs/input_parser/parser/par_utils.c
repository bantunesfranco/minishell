/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 14:24:01 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/31 18:04:42 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

t_cmd	*find_curr_cmd(t_pipeline *curr_pipeline)
{
	t_cmd	*temp;

	temp = curr_pipeline->first_cmd;
	if (temp != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
	}
	return (temp);
}

t_pipeline	*find_curr_pipeline(t_pipeline *first_pipeline)
{
	t_pipeline	*temp;

	temp = first_pipeline;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	check_if_builtin(t_cmd *current_cmd)
{
	if (current_cmd->cmd == NULL)
		return ;
	if (ft_strncmp(current_cmd->cmd[0], "echo", 5) == 0)
	{
		current_cmd->builtin = echo;
	}
}

void	close_simple_cmd(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token)
{
	t_cmd	*current_cmd;

	current_cmd = find_curr_cmd(curr_pipeline);
	if (current_cmd == NULL)
	{
		current_cmd = make_new_simple_cmd();
		curr_pipeline->first_cmd = current_cmd;
	}
	current_cmd->cmd = create_cmd_array(temp, *first_token);
	check_if_builtin(current_cmd);
	remove_tokens(temp, first_token);
}
