/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 16:02:06 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/08 17:38:49 by bfranco       ########   odam.nl         */
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

int	export(t_gen *gen, t_cmd *cmd)
{
	int		size;
	int		replace;
	char	*target;

	if (!cmd->cmd[1])
		return (print_export_env(gen->env), 0);
	size = get_size(gen->env, target, &replace);
	if (replace)
	{
		while (gen->env[i] && ft_envcmp(env[i], target))
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
