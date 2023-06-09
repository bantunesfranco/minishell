/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 16:02:06 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/03 18:09:17 by bfranco       ########   odam.nl         */
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

static int	set_variable(t_gen *gen, t_cmd *cmd, int i, int *ret)
{
	int		size;
	int		add;

	if (ft_strchr(cmd->cmd[i], '='))
	{
		size = get_size(gen->env, cmd->cmd[i], &add) + add;
		if (export2(gen, cmd->cmd[i], add, size) == -1)
			return (err_msg(NULL, cmd->cmd[0]), -1);
	}
	*ret = 0;
	return (0);
}

int	export(t_gen *gen, t_cmd *cmd)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	if (!cmd->cmd[1])
		if (print_export_env(gen->env, cmd->output->fd) == -1)
			return (err_msg(cmd->cmd[0], "write error"), 1);
	while (cmd->cmd[++i])
	{
		if (!ft_strncmp(cmd->cmd[i], "_=", 2))
			continue ;
		if (is_valid_input(cmd->cmd[i]))
		{
			if (set_variable(gen, cmd, i, &ret) == -1)
				return (1);
		}
		else
		{
			ret = 1;
			built_err_msg(cmd->cmd[0], cmd->cmd[i], "not a valid identifier\n");
		}
	}
	return (ret);
}
