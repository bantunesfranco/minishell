/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_subshell_pipeline.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/05 17:51:38 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 17:57:58 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executor.h"

static void	dup_and_close(t_pipeline *pipeline, int p[2], int pipe_read)
{
	if (pipeline->next_control_operator == PIPELINE)
	{
		close(p[0]);
		if (dup2(p[1], STDOUT_FILENO) == -1)
			child_err_msg(NULL, "executor");
		close(p[1]);
	}
	if (pipeline->prev_control_operator == PIPELINE)
	{
		if (dup2(pipe_read, STDIN_FILENO) == -1)
			child_err_msg(NULL, "executor");
		close(pipe_read);
	}
}

static int	setup_pipe_fork(t_pipeline *pipeline, int p[2])
{
	int	id;

	if (pipeline->next_control_operator == PIPELINE)
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
		if (pipeline->next_control_operator == PIPELINE)
		{
			close(p[0]);
			close(p[1]);
		}
		err_msg(NULL, "executor");
	}
	return (id);
}

int	exec_subsh_pipeline(t_gen *gen, t_pipeline **pipeline, int *pipe_read)
{
	int	id;
	int	p[2];

	id = setup_pipe_fork(*pipeline, p);
	if (id == -1)
		return (-1);
	else if (id == 0)
	{
		dup_and_close(*pipeline, p, *pipe_read);
		exec_simple_pipeline(gen, *pipeline);
		_exit(gen->status);
	}
	else
	{
		if ((*pipeline)->prev_control_operator == PIPELINE)
			close(*pipe_read);
		if ((*pipeline)->next_control_operator == PIPELINE)
		{
			close(p[1]);
			*pipe_read = p[0];
		}
		*pipeline = (*pipeline)->next;
	}
	return (id);
}
