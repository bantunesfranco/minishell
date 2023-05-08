/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bruno <bruno@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 19:18:19 by bruno         #+#    #+#                 */
/*   Updated: 2023/05/08 17:22:59 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_size(char **env, char *target, int *delete)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	*delete = 0;
	while (env[i])
	{
		if (!ft_envcmp(env[i], target))
		{
			size--;
			*delete = 1;
		}
		i++;
		size++;
	}
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
		if (!ft_envcmp(env[i], target))
		{
			free(env[i++]);
			if (!env[i])
				break ;
		}
		else
			new_env[j++] = env[i++];
	}
	free(env);
	return (new_env);
}

int	unset(t_gen *gen, t_cmd *cmd)
{
	int		size;
	int		delete;
	char	*target;
	char	**new_env;

	if (!cmd->cmd[1])
		return (0);
	target = ft_strjoin(cmd->cmd[1], "=");
	if (!target)
		return (-1);
	size = get_size(gen->env, target, &delete);
	if (!size || !delete)
		return (free(target), -1);
	new_env = copy_env(gen->env, target, size);
	if (!new_env)
		return (free(target), -1);
	gen->env = new_env;
	return (0);
}
