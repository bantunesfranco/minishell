/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_find_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 12:30:34 by codespace     #+#    #+#                 */
/*   Updated: 2023/05/30 17:19:10 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	find_path(char **cmd, t_gen *gen)
{
	int		i;

	i = 0;
	ft_free_arr(gen->path);
	gen->path = NULL;
	while (gen->env[i])
	{
		if (!ft_envcmp(gen->env[i], "PATH="))
		{
			gen->path = ft_split(gen->env[i] + 5, ':');
			if (!gen->path)
				err_msg(NULL, cmd[0]);
		}
		i++;
	}
	// if (!gen->path)
	// {
	// 	errno = 127;
	// 	err_msg(NULL, cmd[0]);
	// 	exit (127);
	// }
}
