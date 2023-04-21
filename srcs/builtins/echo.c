/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 14:34:50 by bfranco       #+#    #+#                 */
/*   Updated: 2023/04/21 14:44:10 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	option_check(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->cmd[1][0] == '-')
	{
		while (cmd->cmd[1][i] && cmd->cmd[1][i] == 'n')
		{
			i++;
			if (cmd->cmd[1][i] && cmd->cmd[1][i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

int	echo(char **env, t_cmd *cmd)
{
	int	option;

	(void)env;
	option = option_check(cmd);
	if (!cmd->cmd[0] || ft_strlen(*cmd->cmd[0]) == 0)
	{
		if (option)
			return (0);
		if (write(cmd->output->fd, "\n", 1) == -1)
			return (-1);
	}
	else
	{
		if (write(cmd->output->fd, str, ft_strlen(str)) == -1)
			return (-1);
		if (option)
			return (0);
		if (write(cmd->output->fd, "\n", 1) == -1)
			return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;
	int		i;
	t_cmd	cmd;
	t_cmd	cmd2;

	i = 0;
	(void)argc;
	cmd.cmd = ft_split(argv[1], ' ');
	env = ft_arrdup(envp);
	echo(env, &cmd)
	ft_free_arr(env);
	exit(0);
}
