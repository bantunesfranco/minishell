/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 14:24:01 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/29 14:10:55 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parsing.h"
#include "parsing_structs.h"
#include <stdlib.h>

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
	remove_tokens(temp, first_token);
}
