/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 13:31:57 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/23 11:39:07 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_target(char *cmd, int *join)
{
	char	*target;
	int		i;

	i = 0;
	while (cmd[i] && (cmd[i] != '=' || (cmd[i] == '+' && cmd[i + 1] == '=')))
		i++;
	target = ft_calloc(i + 2, sizeof(char));
	if (!target)
		return (0);
	i = 0;
	while (cmd[i] && (cmd[i] != '=' || (cmd[i] == '+' && cmd[i + 1] == '=')))
	{
		target[i] = cmd[i];
		i++;
		if (cmd[i] == '+' && cmd[i + 1] == '=')
			*join = 1;
	}
	target[i] = '=';
	return (target);
}

char	*dup_target(char *target)
{
	int		i;
	int		j;
	char	*var;
	char	*str;

	i = ft_strlen(target);
	j = 0;
	var = get_target(target, &j);
	if (!var)
		return (NULL);
	if (ft_strchr(var, '+'))
		j = 1;
	str = ft_calloc(i - j + 1, sizeof(char));
	if (!str)
		return (NULL);
	j = ft_strlen(var) - j - 1;
	ft_memmove(str, var, j);
	str[j] = '=';
	ft_memmove(str + j, ft_strchr(target, '='), i - j + 1);
	free(var);
	return (str);
}

char	**copy_env(char **env, char *target, int size)
{
	int		i;
	char	**new_env;

	i = 0;
	if (size == 0)
		return (env);
	new_env = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	free(env);
	new_env[i] = dup_target(target);
	if (!new_env[i])
		return (err_msg(NULL, "env"), NULL);
	return (new_env);
}

static char	*export_type(char *cmd, char *temp, int join)
{
	char	*str;

	if (join)
		str = ft_strjoin(temp, ft_strchr(cmd, '=') + 1);
	else
		str = ft_strdup(cmd);
	if (str)
		free(temp);
	return (str);
}

int	export2(t_gen *gen, char *cmd, int add, int size)
{
	int		i;
	char	*target;
	int		join;
	char	*temp;

	i = 0;
	join = 0;
	target = get_target(cmd, &join);
	if (!target || ft_strlen(target) == 1)
		return (-1);
	if (!add)
	{
		while (gen->env[i] && ft_envcmp(gen->env[i], target))
			i++;
		temp = gen->env[i];
		gen->env[i] = export_type(cmd, temp, join);
		if (!gen->env[i])
			return (free(target), -1);
	}
	else
		gen->env = copy_env(gen->env, cmd, size);
	return (free(target), 0);
}
