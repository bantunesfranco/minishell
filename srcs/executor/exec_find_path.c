/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_find_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 12:30:34 by codespace     #+#    #+#                 */
/*   Updated: 2023/05/26 09:35:28 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"


char	**find_path(char **cmd, char **env)
{
	int		i;
	char	**path_arr;

	i = 0;
	path_arr = NULL;
	while (env[i])
	{
		if (!ft_envcmp(env[i], "PATH="))
		{
			path_arr = ft_split(env[i] + 5, ':');
			if (!path_arr)
				return (err_msg(NULL, cmd[0]), NULL);
		}
		i++;
	}
	if (!path_arr)
	{
		errno = 127;
		err_msg(NULL, cmd[0]);
		exit (127);
	}
	else
		return (path_arr);
}
