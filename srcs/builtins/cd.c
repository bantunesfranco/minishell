/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 16:53:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/04 10:54:05 by bruno         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static char	*get_target(char *target, t_gen *gen)
{
	int	i;

	i = 0;
	if (!ft_strncmp(target, "OLDPWD=", 8))
		return (ft_strdup(gen->oldpwd));
	else if (!ft_strncmp(target, "HOME=", 5))
	{
		while (gen->env[i])
		{
			if (!ft_strncmp(gen->env[i], "HOME=", 5))
				return (ft_strdup(gen->env[i] + 5));
			i++;
		}
		return (NULL);
	}
	else
		return (ft_strdup(target));
}

static int	go_to(char *target, t_gen *gen)
{
	target = get_target(target, gen);
	if (!target)
		return (-1);
	free(gen->oldpwd);
	gen->oldpwd = getcwd(NULL, 1);
	if (!gen->oldpwd)
		return (-1);
	if (chdir(target) == -1)
		return (-1);
	free(target);
	free(gen->pwd);
	gen->pwd = getcwd(NULL, 1);
	if (!gen->pwd)
		return (-1);
	return (0);
}

int	cd(t_gen *gen, t_cmd *cmd)
{
	if (!cmd->cmd[1])
	{
		if (go_to("HOME=", gen) == -1)
			return (-1);
	}
	else if (!ft_strncmp(cmd->cmd[1], "-", 2))
	{
		if (go_to("OLDPWD=", gen) == -1)
			return (-1);
	}
	else
	{
		if (go_to(cmd->cmd[1], gen) == -1)
			return (-1);
	}
	return (0);
}
