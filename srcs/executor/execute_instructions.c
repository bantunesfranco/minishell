/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_instructions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 16:39:50 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/03 16:40:17 by jmolenaa      ########   odam.nl         */
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

	// printf("%d\n", (*subshell)->subshell->pipe_output);
	// printf("%d\n", (*subshell)->subshell->pipe_input);
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
		// printf("%p\n", (*subshell)->subshell);
		// printf("fiss%p\n", (*subshell)->first_cmd);
		// // printf("%s\n", (*subshell)->first_cmd->cmd[0]);
		// printf("fz2%p\n", (*subshell)->next->first_cmd);
		// printf("%s\n", (*subshell)->next->first_cmd->cmd[0]);
		// printf("lololol%p\n", (*subshell)->next->subshell);
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
		{
			// dprintf(2, "here\n");
			id = execute_subshell(gen, &tmp, &pipe_read);
			// printf("tmp-%p\n", tmp->subshell);
		}
		else if (tmp->next_control_operator == PIPE || tmp->prev_control_operator == PIPE)
		{
			// dprintf(2, "not\n"); 
			id = execute_pipeline(gen, &tmp, &pipe_read);
		}
		else
			break ; 
		if (tmp && (tmp->prev_control_operator == CLOSE || \
			tmp->prev_control_operator == OR || \
			tmp->prev_control_operator == AND))
			break;
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
	// printf("%p\n", tmp);
	// printf("%p\n", tmp->first_cmd);
	// printf("%s\n", tmp->first_cmd->cmd[0]);
	return (tmp);
}

void	execute_instructions(t_gen *gen, t_pipeline *input)
{
	t_pipeline *tmp;

	tmp = input;
	while (tmp != NULL)
	{
		if (tmp->prev_control_operator == CLOSE)
		{
			// dprintf(2, "HALLELUJA\n");
			break ;
		}
		else if (tmp->next_control_operator == OPEN || tmp->next_control_operator == PIPE)
		{
			// dprintf(2, "huh\n");
			// printf("%d\n", tmp->next_control_operator);
			tmp = execute_pipeline_list(gen, tmp);
		}
		else
		{
			// dprintf(2, "hi\n");
			executor(gen, tmp);
			tmp = tmp->next;
		}
		if (tmp != NULL)// && tmp->next)
		{
			tmp = check_control_operators(gen, tmp);
			// dprintf(2, "%p\n", tmp);
		}
		else
		{
			// printf("aodkoasd\n");
			break ;
		}
	}
}

