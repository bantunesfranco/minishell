/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_cmd_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 09:58:21 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/27 10:26:08 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>

void	free_redirect_list(t_redirect *first_redirect)
{
	t_redirect	*temp;

	while (first_redirect != NULL)
	{
		temp = first_redirect;
		first_redirect = first_redirect->next;
		free(temp->name);
		free(temp->str);
		free(temp);
	}
}

void	free_subshell_struct(t_subshell *subshell)
{
	if (subshell == NULL)
		return ;
	free_redirect_list(subshell->input);
	free_redirect_list(subshell->output);
	free(subshell);
}

void	free_cmd_array(char **cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return ;
	while (*(cmd + i) != NULL)
	{
		free(*(cmd + i));
		i++;
	}
	free(cmd);
}

void	free_simple_commands(t_cmd *first_cmd)
{
	t_cmd	*temp;

	while (first_cmd != NULL)
	{
		temp = first_cmd;
		first_cmd = first_cmd->next;
		free_redirect_list(temp->input);
		free_redirect_list(temp->output);
		free_cmd_array(temp->cmd);
		free(temp);
	}
}

void	free_parsed_structs(t_pipeline *first_pipeline)
{
	t_pipeline	*temp;

	while (first_pipeline != NULL)
	{
		free_subshell_struct(first_pipeline->subshell);
		free_simple_commands(first_pipeline->first_cmd);
		temp = first_pipeline;
		first_pipeline = first_pipeline->next;
		free(temp);
	}
}
