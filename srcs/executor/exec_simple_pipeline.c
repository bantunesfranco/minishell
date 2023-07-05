/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_simple_pipeline.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 07:51:09 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/05 18:21:31 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "expander.h"

int	is_builtin(t_gen *gen, t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->builtin && !cmd->next)
	{
		cmd->input->fd = handle_input_redirection(cmd->input, gen);
		if (cmd->input->fd == -1)
		{
			gen->status = 1;
			return (1);
		}
		cmd->output->fd = handle_output_redirection(cmd->output, gen);
		if (cmd->output->fd == -1)
		{
			gen->status = 1;
			return (1);
		}
		gen->status = cmd->builtin(gen, cmd);
		return (1);
	}
	return (0);
}

void	exec_cmd(t_gen *gen, t_cmd *cmd, int *p, int pipe_rd)
{
	if (cmd->next)
		close(p[0]);
	cmd->input->fd = handle_input_redirection(cmd->input, gen);
	if (cmd->input->fd == -1)
		_exit (1);
	cmd->output->fd = handle_output_redirection(cmd->output, gen);
	if (cmd->output->fd == -1)
		_exit (1);
	handle_dups(cmd, p, pipe_rd);
	if (cmd->cmd == NULL)
		_exit(EXIT_SUCCESS);
	else if (cmd->builtin)
		_exit(cmd->builtin(gen, cmd));
	else
	{
		close_pipes(cmd, p, pipe_rd);
		find_path(cmd->cmd, gen);
		check_access(gen, cmd);
		execve(cmd->path, cmd->cmd, gen->env);
		errno = 127;
		child_err_msg(NULL, cmd->cmd[0]);
	}
}

int	cmd_loop(t_gen *gen, t_cmd *cmd, int *p)
{
	int		id;
	int		pipe_rd;

	pipe_rd = 0;
	while (cmd)
	{
		id = pipe_and_fork(cmd, p);
		if (id == -1)
			return (-1);
		if (id == 0)
			exec_cmd(gen, cmd, p, pipe_rd);
		if (cmd->next)
		{
			if (cmd->prev)
				close(pipe_rd);
			pipe_rd = p[0];
		}
		if (cmd->next)
			close(p[1]);
		else if (cmd->prev)
			close (pipe_rd);
		cmd = cmd->next;
	}
	return (id);
}

void	exec_simple_pipeline(t_gen *gen, t_pipeline *pipeline)
{
	t_cmd	*cmd;
	int		p[2];
	int		id;

	if (pipeline->subshell)
		return ;
	cmd = pipeline->first_cmd;
	expand_pipeline(cmd, gen);
	check_pipeline_for_builtins(cmd);
	if (is_builtin(gen, cmd) == 1)
		return ;
	id = cmd_loop(gen, cmd, p);
	if (id == -1)
	{
		gen->status = 1;
		return ;
	}
	waitpid(id, &gen->status, 0);
	if (WIFEXITED(gen->status))
		gen->status = WEXITSTATUS(gen->status);
	else if (WIFSIGNALED(gen->status))
		gen->status = 128 + WTERMSIG(gen->status);
	while (1)
		if (wait(NULL) == -1)
			break ;
}
