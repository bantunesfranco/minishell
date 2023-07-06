/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_instructions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 16:39:50 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 17:54:28 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executor.h"

t_pipeline	*pipeline_list_loop(t_gen *gen, t_pipeline *first_pipeline, int *id)
{
	t_pipeline	*tmp;
	int			pipe_read;

	pipe_read = 0;
	tmp = first_pipeline;
	while (tmp != NULL)
	{
		if (tmp->next_control_operator == OPEN)
			*id = exec_subsh(gen, &tmp, &pipe_read);
		else if (tmp->next_control_operator == PIPELINE \
				|| tmp->prev_control_operator == PIPELINE)
			*id = exec_subsh_pipeline(gen, &tmp, &pipe_read);
		else
			break ;
		if (*id == -1)
		{
			gen->status = 1;
			return (NULL);
		}
		else if (tmp && (tmp->prev_control_operator == CLOSE \
					|| tmp->prev_control_operator == OR \
					|| tmp->prev_control_operator == AND))
			break ;
	}
	return (tmp);
}

t_pipeline	*execute_pipeline_list(t_gen *gen, t_pipeline *first_pipeline)
{
	t_pipeline	*next_pipeline;
	int			id;

	next_pipeline = pipeline_list_loop(gen, first_pipeline, &id);
	waitpid(id, &gen->status, 0);
	if (WIFEXITED(gen->status))
		gen->status = WEXITSTATUS(gen->status);
	else if (WIFSIGNALED(gen->status))
		gen->status = 128 + WTERMSIG(gen->status);
	while (1)
		if (wait(NULL) == -1)
			break ;
	return (next_pipeline);
}

void	execute_instructions(t_gen *gen, t_pipeline *input)
{
	t_pipeline	*tmp;

	tmp = input;
	while (tmp != NULL)
	{
		if (tmp->prev_control_operator == CLOSE)
			break ;
		else if (tmp->next_control_operator == OPEN || \
				tmp->next_control_operator == PIPELINE)
			tmp = execute_pipeline_list(gen, tmp);
		else
		{
			exec_simple_pipeline(gen, tmp);
			tmp = tmp->next;
		}
		if (tmp != NULL)
			tmp = check_control_operators(gen, tmp);
	}
}
