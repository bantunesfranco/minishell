/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_instructions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 16:39:50 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/04 19:11:44 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executor.h"

int	execute_pipeline(t_gen *gen, t_pipeline **pipeline, int *pipe_read)
{
	int	id;
	int	p[2];

	if ((*pipeline)->next_control_operator == PIPE)
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
	else if (id == 0)
	{
		if ((*pipeline)->next_control_operator == PIPE)
		{
			close(p[0]);
			if (dup2(p[1], STDOUT_FILENO) == -1)
				child_err_msg(NULL, "executor");
			close(p[1]);
		}
		if ((*pipeline)->prev_control_operator == PIPE)
		{
			if (dup2(*pipe_read, STDIN_FILENO) == -1)
				child_err_msg(NULL, "executor");
			close(*pipe_read);
		}
		executor(gen, *pipeline);
		_exit(gen->status);
	}
	else
	{
		if ((*pipeline)->prev_control_operator == PIPE)
		{
			close(*pipe_read);
		}
		if ((*pipeline)->next_control_operator == PIPE)
		{
			close(p[1]);
			*pipe_read = p[0];
		}
		*pipeline = (*pipeline)->next;
	}
	return (id);
}

int	execute_subshell(t_gen *gen, t_pipeline **subshell, int *pipe_read)
{
	int	id;
	int	p[2];

	if ((*subshell)->subshell->pipe_output == 1)
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
	else if (id == 0)
	{
		if ((*subshell)->subshell->pipe_output == 1)
			close(p[0]);
		(*subshell)->subshell->input->fd = handle_input_redirection((*subshell)->subshell->input, gen);
		if ((*subshell)->subshell->input->fd == -1)
			_exit (1);
		(*subshell)->subshell->output->fd = handle_output_redirection((*subshell)->subshell->output, gen);
		if ((*subshell)->subshell->output->fd == -1)
			_exit (1);
		if ((*subshell)->subshell->pipe_output == 1 && (*subshell)->subshell->output->fd == STDOUT_FILENO)
		{
			// close(p[0]);
			if (dup2(p[1], STDOUT_FILENO) == -1)
				child_err_msg(NULL, "executor");
			// close(p[1]);
		}
		if ((*subshell)->subshell->pipe_input == 1 && (*subshell)->subshell->input->fd == STDIN_FILENO)
		{
			if (dup2(*pipe_read, STDIN_FILENO) == -1)
				child_err_msg(NULL, "executor");
			// close(*pipe_read);
		}
		if ((*subshell)->subshell->output->fd != STDOUT_FILENO)
		{
			if (dup2((*subshell)->subshell->output->fd, STDOUT_FILENO) == -1)
				child_err_msg(NULL, "executor");
		}
		if ((*subshell)->subshell->input->fd != STDIN_FILENO)
		{
			if (dup2((*subshell)->subshell->input->fd, STDIN_FILENO) == -1)
				child_err_msg(NULL, "executor");
		}
		if ((*subshell)->subshell->pipe_input == 1)
			close(*pipe_read);
		if ((*subshell)->subshell->pipe_output == 1)
			close(p[1]);
		if ((*subshell)->subshell->input->fd != STDIN_FILENO)
			close((*subshell)->subshell->input->fd);
		if ((*subshell)->subshell->output->fd != STDOUT_FILENO)
			close((*subshell)->subshell->output->fd);
		execute_instructions(gen, (*subshell)->next);
		_exit(gen->status);
	}
	else
	{
		if ((*subshell)->subshell->pipe_input == 1)
		{
			close(*pipe_read);
		}
		if ((*subshell)->subshell->pipe_output == 1)
		{
			close(p[1]);
			*pipe_read = p[0];
		}
		*subshell = goto_close_operator(*subshell);
	}
	return (id);
}

t_pipeline	*execute_pipeline_list(t_gen *gen, t_pipeline *first_pipeline)
{
	t_pipeline	*tmp;
	int			id;
	int			pipe_read;

	pipe_read = 0;
	tmp = first_pipeline;
	while (tmp != NULL)
	{
		if (tmp->next_control_operator == OPEN)
			id = execute_subshell(gen, &tmp, &pipe_read);
		else if (tmp->next_control_operator == PIPE || tmp->prev_control_operator == PIPE)
			id = execute_pipeline(gen, &tmp, &pipe_read);
		else
			break ;
		if (tmp && (tmp->prev_control_operator == CLOSE \
		|| tmp->prev_control_operator == OR \
		|| tmp->prev_control_operator == AND))
			break ;
		// tmp = tmp->next;
	}
	waitpid(id, &gen->status, 0);
	if (WIFEXITED(gen->status))
	{
		gen->status = WEXITSTATUS(gen->status);
	}
	else if (WIFSIGNALED(gen->status))
		gen->status = 128 + WTERMSIG(gen->status);
	while (1)
		if (wait(NULL) == -1)
			break ;
	return (tmp);
}

void	execute_instructions(t_gen *gen, t_pipeline *input)
{
	t_pipeline	*tmp;

	tmp = input;
	while (tmp != NULL)
	{
		if (tmp->prev_control_operator == CLOSE)
			break ;
		else if (tmp->next_control_operator == OPEN || tmp->next_control_operator == PIPE)
			tmp = execute_pipeline_list(gen, tmp);
		else
		{
			executor(gen, tmp);
			tmp = tmp->next;
		}
		if (tmp != NULL)
			tmp = check_control_operators(gen, tmp);
		else
			break ;
	}
}
