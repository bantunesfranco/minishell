/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_subshell.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/05 15:32:06 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 18:22:05 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executor.h"

void	handle_subshell_dups(t_subshell *subshell, int p[2], int pipe_read)
{
	if (subshell->pipe_output == 1 && subshell->output->fd == STDOUT_FILENO)
	{
		if (dup2(p[1], STDOUT_FILENO) == -1)
			child_err_msg(NULL, "executor");
	}
	if (subshell->pipe_input == 1 && subshell->input->fd == STDIN_FILENO)
	{
		if (dup2(pipe_read, STDIN_FILENO) == -1)
			child_err_msg(NULL, "executor");
	}
	if (subshell->output->fd != STDOUT_FILENO)
	{
		if (dup2(subshell->output->fd, STDOUT_FILENO) == -1)
			child_err_msg(NULL, "executor");
	}
	if (subshell->input->fd != STDIN_FILENO)
	{
		if (dup2(subshell->input->fd, STDIN_FILENO) == -1)
			child_err_msg(NULL, "executor");
	}
}

void	close_open_fds(t_subshell *subshell, int p[2], int pipe_read)
{
	if (subshell->pipe_input == 1)
		close(pipe_read);
	if (subshell->pipe_output == 1)
		close(p[1]);
	if (subshell->input->fd != STDIN_FILENO)
		close(subshell->input->fd);
	if (subshell->output->fd != STDOUT_FILENO)
		close(subshell->output->fd);
}

void	child_subsh(t_gen *gen, t_pipeline *pipeline, int *pipe_read, int p[2])
{
	t_subshell	*subsh;

	subsh = pipeline->subshell;
	if (subsh->pipe_output == 1)
		close(p[0]);
	subsh->input->fd = handle_input_redirection(subsh->input, gen);
	if (subsh->input->fd == -1)
		_exit (1);
	subsh->output->fd = handle_output_redirection(subsh->output, gen);
	if (subsh->output->fd == -1)
		_exit (1);
	handle_subshell_dups(subsh, p, *pipe_read);
	close_open_fds(subsh, p, *pipe_read);
	execute_instructions(gen, pipeline->next);
	_exit(gen->status);
}

static int	setup_pipe_fork(t_subshell *subshell, int p[2])
{
	int	id;

	if (subshell->pipe_output == 1)
	{
		if (pipe(p) == -1)
		{
			err_msg(NULL, "executor");
			return (-1);
		}
	}
	id = fork();
	if (id == -1)
	{
		if (subshell->pipe_output == 1)
		{
			close(p[0]);
			close(p[1]);
		}
		err_msg(NULL, "executor");
	}
	return (id);
}

int	exec_subsh(t_gen *gen, t_pipeline **pipeline, int *pipe_read)
{
	int			id;
	int			p[2];
	t_subshell	*subsh;

	subsh = (*pipeline)->subshell;
	id = setup_pipe_fork(subsh, p);
	if (id == -1)
		return (-1);
	else if (id == 0)
		child_subsh(gen, *pipeline, pipe_read, p);
	else
	{
		if (subsh->pipe_input == 1)
			close(*pipe_read);
		if (subsh->pipe_output == 1)
		{
			close(p[1]);
			*pipe_read = p[0];
		}
		*pipeline = goto_close_operator(*pipeline);
	}
	return (id);
}
