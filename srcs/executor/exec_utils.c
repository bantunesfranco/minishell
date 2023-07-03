/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 16:42:33 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/03 16:43:00 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executor.h"

t_pipeline	*goto_close_operator(t_pipeline *tmp)
{
	int		open;
	int		close;
	
	open = 1;
	close = 0;
	while (tmp && open - close != 0)
	{
		tmp = tmp->next;
		if (!tmp)
			break ;
		if (tmp->next_control_operator == OPEN)
			open++;
		if (tmp->next_control_operator == CLOSE)
			close++;
	}
	if (tmp && tmp->next_control_operator == CLOSE)
		tmp = tmp->next->next;
	return (tmp);
}

t_pipeline	*check_control_operators(t_gen *gen, t_pipeline *tmp)
{
	if (tmp->prev_control_operator == CLOSE || tmp->prev_control_operator == OPEN)
		return (tmp);
	while (tmp)
	{
		if (tmp->prev_control_operator == AND && gen->status == 0)
			return (tmp);
		else if (tmp->prev_control_operator == OR && gen->status != 0)
			return (tmp);
		else if (tmp->next && tmp->next_control_operator == OPEN)
			tmp = goto_close_operator(tmp);
		else
			tmp = tmp->next;
		if (tmp && tmp->prev_control_operator == CLOSE)
			break ;
	}
	return (tmp);
}
