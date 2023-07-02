/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipes_dups.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 14:08:38 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/02 15:20:00 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	handle_dups(t_cmd *cmd, int *p, int pipe_rd)
{
	if (cmd->prev && cmd->input->fd == STDIN_FILENO)
		if (dup2(pipe_rd, STDIN_FILENO) == -1)
			child_err_msg(NULL, "executor");
	if (cmd->next && cmd->output->fd == STDOUT_FILENO)
		if (dup2(p[1], STDOUT_FILENO) == -1)
			child_err_msg(NULL, "executor");
	if (cmd->input->fd != STDIN_FILENO)
	{
		if (dup2(cmd->input->fd, STDIN_FILENO) == -1)
			child_err_msg(NULL, "executor");
	}
	if (cmd->output->fd != STDOUT_FILENO)
	{
		if (dup2(cmd->output->fd, STDOUT_FILENO) == -1)
			child_err_msg(NULL, "executor");
	}
}

int	pipe_and_fork(t_cmd *cmd, int *p)
{
	int	id;

	if (cmd->next)
	{
		if (pipe(p) == -1)
		{
			err_msg(NULL, "executor");
			return (-1);
		}
	}
	else
	{
		p[0] = -1;
		p[1] = -1;
	}
	id = fork();
	if (id == -1)
	{
		err_msg(NULL, "executor");
		return (-1);
	}
	return (id);
}

void	close_pipes(t_cmd *cmd, int *p, int pipe_rd)
{
	if (cmd->prev != NULL)
		close(pipe_rd);
	if (cmd->next != NULL)
		close(p[1]);
	if (cmd->input->fd != STDIN_FILENO)
		close(cmd->input->fd);
	if (cmd->output->fd != STDOUT_FILENO)
		close(cmd->output->fd);
}
