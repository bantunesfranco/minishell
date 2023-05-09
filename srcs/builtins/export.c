/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 16:02:06 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/09 10:45:45 by bruno         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_size(char **env, char *target, int *replace)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	*replace = 0;
	while (env[i])
	{
		if (!ft_envcmp(env[i], target))
			*replace = 1;
		i++;
		size++;
	}
	if (!*replace)
		size++;
	return (size);
}

static char	**copy_env(char **env, char *target, int size)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	if (size == 0)
		return (env);
	new_env = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		new_env[j] = env[i];
		i++;
		j++;
	}
	free(env);
	new_env[i] = ft_strdup(target);
	if (!new_env[i])
		return (NULL);
	return (new_env);
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
		i++;
	}
	return (0);
}

int	export(t_gen *gen, t_cmd *cmd)
{
	int		size;
	int		replace;
	char	*target;
	int		i;

	i = 0;
	size = get_size(gen->env, target, &replace);
	if (!cmd->cmd[1])
		return (print_export_env(gen->env, cmd->output->fd));
	if (replace)
	{
		while (gen->env[i] && ft_envcmp(gen->env[i], target))
			i++;
		free(gen->env[i]);
		gen->env[i] = ft_strdup(cmd->cmd[1]);
		if (!gen->env[i])
			return (-1);
	}
	else
	{
		free(gen->env);
		gen->env = copy_env(gen->env, cmd->cmd[1], size);
	}
	return (0);
}
