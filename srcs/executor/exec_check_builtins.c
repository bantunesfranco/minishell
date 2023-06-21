/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_check_builtins.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/21 13:47:34 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/21 13:51:06 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

void	check_if_builtin(t_cmd *current_cmd)
{
	if (current_cmd->cmd == NULL)
		return ;
	if (ft_strncmp(current_cmd->cmd[0], "cd", 3) == 0)
		current_cmd->builtin = cd;
	else if (ft_strncmp(current_cmd->cmd[0], "echo", 5) == 0)
		current_cmd->builtin = echo;
	else if (ft_strncmp(current_cmd->cmd[0], "env", 4) == 0)
		current_cmd->builtin = env;
	else if (ft_strncmp(current_cmd->cmd[0], "exit", 5) == 0)
		current_cmd->builtin = mini_exit;
	else if (ft_strncmp(current_cmd->cmd[0], "export", 7) == 0)
		current_cmd->builtin = export;
	else if (ft_strncmp(current_cmd->cmd[0], "pwd", 4) == 0)
		current_cmd->builtin = pwd;
	else if (ft_strncmp(current_cmd->cmd[0], "unset", 6) == 0)
		current_cmd->builtin = unset;
}

void	check_pipeline_for_builtins(t_cmd *first_cmd)
{
	t_cmd	*temp;

	temp = first_cmd;
	while (temp != NULL)
	{
		check_if_builtin(temp);
		temp = temp->next;
	}
}
