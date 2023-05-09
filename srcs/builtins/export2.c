/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 13:31:57 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/09 14:50:03 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_target(char *cmd)
{
	char	*target;
	int		i;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	target = ft_calloc(i + 2, sizeof(char));
	if (!target)
		return (0);
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		target[i] = cmd[i];
		i++;
	}
	target[i] = cmd[i];
	return (target);
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

int	export2(t_gen *gen, char *cmd, int add, int size)
{
	int		i;
	char	*target;

	i = 0;
	target = get_target(cmd);
	if (!target)
		return (-1);
	if (!add)
	{
		while (gen->env[i] && ft_envcmp(gen->env[i], target))
			i++;
		if (!gen->env[i])
			return (free(target), 0);
		free(gen->env[i]);
		gen->env[i] = ft_strdup(cmd);
		if (gen->env[i])
			return (free(target), -1);
	}
	else
		gen->env = copy_env(gen->env, cmd, size);
	return (free(target), 0);
}
