/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 16:02:06 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/09 14:55:42 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_size(char **env, char *target, int *add)
{
	int	i;

	i = 0;
	*add = 1;
	while (env[i])
	{
		if (!ft_envcmp(env[i], target))
			*add = 0;
		i++;
	}
	return (i);
}

static int	print_export_env(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (write(fd, "declare -x ", 11) == -1)
			return (-1);
		if (write(fd, env[i], ft_strlen(env[i])) == -1)
			return (-1);
		if (write(fd, "\n", 1) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	export(t_gen *gen, t_cmd *cmd)
{
	int		size;
	int		add;

	if (!cmd->cmd[1])
		return (print_export_env(gen->env, cmd->output->fd));
	size = get_size(gen->env, cmd->cmd[1], &add) + add;
	if (export2(gen, cmd->cmd[1], add, size) == -1)
		return (-1);
	return (0);
}
