/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 16:42:33 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/08 11:02:18 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include <dirent.h>
#include "executor.h"

void	is_dir(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir == NULL)
		return ;
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": is a directory\n", 18);
	closedir(dir);
	_exit(126);
}

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
	if (tmp->prev_control_operator == CLOSE \
		|| tmp->prev_control_operator == OPEN)
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

int	handle_signal(int status)
{
	int	signal;

	signal = WTERMSIG(status);
	if (signal == 2)
		write(1, "\n", 1);
	else if (signal == 3)
		write(0, "Quit: 3\n", 8);
	return (128 + signal);
}
