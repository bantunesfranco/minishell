/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 16:02:06 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/04 16:54:08 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i])
		i++;
	return (i);
}

static void	which_operation(char **env, char **cmd, int *op)
{
	int		i;
	char	*str;
	char	*str2;

	i = 0;
	if (!cmd[1])
		*op = 0;
	else
	{
		*op = 1;
		while (env[i])
		{
			str = ft_substr()
			if (!ft_strnstr(env[i], cmd[1], ft_strlen))
			i++;
		}
	}
}

int	export(t_gen *gen, t_cmd *cmd)
{
	int		size;
	char	**new_env;
	int		i;
	int		operation;

	which_operation(gen->env, cmd->cmd, &operation)
	if (operation == 1)
		size = get_arr_size(gen->env) + 1;
	else
		size = get_arr_size(gen->env);
	new_env = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (-1);
	i = 0;
	while (gen->env[i] && i < size)
	{
		new_env[i] = gen->env[i];
		i++;
	}
	free(gen->env);
	new_env[i] = ft_strdup(cmd->cmd[1]);
	if (!new_env[i])
		return (-1);
	gen->env = new_env;
	return (0);
}
