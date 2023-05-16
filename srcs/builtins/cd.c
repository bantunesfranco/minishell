/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 17:14:18 by codespace     #+#    #+#                 */
/*   Updated: 2023/05/16 17:56:47 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*get_target(char *target, t_gen *gen)
{
	int		i;
	char	*path;

	i = 0;
	while (gen->env[i])
	{
		if (!ft_envcmp(gen->env[i], target))
			return (ft_strdup(ft_strchr(gen->env[i], '=') + 1))
		i++;
	}
	if (!ft_envcmp(target, "OLDPWD=", 8) || !ft_strncmp(target, "HOME=", 5))
	{
		path = ft_substr(target, 0, ft_strlen(target));
		if (!path)
			return (err_msg(NULL, "cd"), NULL);
		return (built_err_msg("cd", NULL))
	}
	else
	{
		path = ft_strdup(target);
		if (!path)
			return (err_msg(NULL, "cd"), NULL);
		return (path);
	}
}

static int	go_to(char *target, t_gen *gen)
{
	target = get_target(target, gen);
	if (!target)
		return (-1);
	if (chdir(target) == -1)
		return (free(target), -1);
	free(target);
	return (0);
}

int	cd(t_gen * gen, t_cmd *cmd)
{
	if (ft_arrlen(cmd->cmd) > 2)
		return (built_err_msg(cmd->cmd[0], NULL, "too many arguments\n"), -1);
	if (!cmd->cmd[1] | !ft_strncmp(cmd->cmd[1], "--", 3))
	{
		if (go_to("HOME=", gen) == -1)
			return (-1);
	}
	else if (!ft_strncmp(cmd->cmd[1], "-", 2))
	{
		if (go_to("OLDPWD=", gen) == -1)
			return (-1);
		if (write(cmd->output->fd, gen->pwd, ft_strlen(gen->pwd)) == -1)
			return (-1);
		if (write(cmd->output->fd, "\n", 1) == -1)
			return (-1);
	}
	else
	{
		if (go_to(cmd->cmd[1], gen) == -1)
			return (-1);
	}
	return (0);
}