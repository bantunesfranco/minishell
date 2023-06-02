/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 07:51:09 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/02 10:45:55 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	is_builtin(t_gen *gen, t_cmd *cmd)
{
	cmd->input->fd = handle_input_redirection(cmd->input);
	cmd->output->fd = handle_output_redirection(cmd->output);
	if (!cmd->next)
	{
		if (cmd->builtin)
		{
			gen->status = cmd->builtin(gen, cmd);
			return (1);
		}
	}
	return (0);
}

void	exec_cmd(t_gen *gen, t_cmd *cmd, int *p, int pipe_rd)
{
	close(p[0]);
	cmd->input->fd = handle_input_redirection(cmd->input);
	cmd->output->fd = handle_output_redirection(cmd->output);
	handle_dups(cmd, p, pipe_rd);
	if (cmd->builtin)
		_exit(cmd->builtin(gen, cmd));
	else
	{
		find_path(cmd->cmd, gen);
		check_access(gen, cmd);
		close_pipes(cmd, p, pipe_rd);
		execve(cmd->path, cmd->cmd, gen->env);
		child_err_msg(NULL, cmd->cmd[0]);
	}
}

void	executor(t_gen *gen, t_pipeline *pipeline)
{
	t_cmd	*cmd;
	int		p[2];
	int		id;
	int		pipe_rd;
	// int		pipe_rd2;

	id = 42;
	cmd = pipeline->first_cmd;
	pipe_rd = 0;
	if (is_builtin(gen, cmd) == 1)
		return ;
	while (cmd)
	{
		id = pipe_and_fork(cmd, p);
		if (id == -1)
			return ;
		if (id == 0)
			exec_cmd(gen, cmd, p, pipe_rd);
		if (p[0] != -1)
			pipe_rd = p[0];
		if (cmd->next)
			close(p[1]);
		cmd = cmd->next;
	}
	// printf("id = %d\n", id);
	wait(NULL);
	waitpid(id, &gen->status, 0);
}
