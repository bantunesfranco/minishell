/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bruno <bruno@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 19:18:19 by bruno         #+#    #+#                 */
/*   Updated: 2023/07/05 15:33:53 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_size(char **env, char *target, int *delete)
{
	int	i;

	i = 0;
	*delete = 0;
	while (env[i])
	{
		if (!ft_envcmp(env[i], target))
			*delete = 1;
		i++;
	}
	return (i);
}

static char	**copy_env2(char **env, char *target, int size)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		if (!ft_envcmp(env[i], target))
			free(env[i++]);
		else
			new_env[j++] = env[i++];
	}
	free(env);
	free(target);
	return (new_env);
}

static int	exec_unset(t_gen *gen, char *cmd, int *ret)
{
	char	**new_env;
	char	*target;
	int		delete;
	int		size;

	target = ft_strjoin(cmd, "=");
	if (!target)
		return (-1);
	size = get_size(gen->env, target, &delete) - delete;
	if (!delete)
		return (free(target), 0);
	new_env = copy_env2(gen->env, target, size);
	if (!new_env)
		return (free(target), -1);
	gen->env = new_env;
	*ret = 0;
	return (0);
}

int	unset(t_gen *gen, t_cmd *cmd)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (cmd->cmd[++i])
	{
		if (!ft_strncmp(cmd->cmd[i], "_", 2))
			continue ;
		if (is_valid_input(cmd->cmd[i]) && !ft_strchr(cmd->cmd[i], '='))
		{
			if (exec_unset(gen, cmd->cmd[i], &ret) == -1)
				return (err_msg(NULL, cmd->cmd[0]), 1);
		}
		else
		{
			ret = 1;
			built_err_msg(cmd->cmd[0], cmd->cmd[i], "not a valid identifier\n");
		}
	}
	return (ret);
}
