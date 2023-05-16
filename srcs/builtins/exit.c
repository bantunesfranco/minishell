/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 16:21:10 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/12 10:46:27 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	atoi_exit(char *str)
{
	long long	nb;
	int			i;

	i = 0;
	nb = 0;
	if (!ft_strlen(str) || str[0] == '-')
		return (-1);
	if (str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			nb = nb * 10 + (str[i] - '0');
			i++;
			if (nb < 0 || nb > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return ((int)(nb));
}

int	mini_exit(t_gen *gen, t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (ft_arrlen(cmd->cmd) > 2)
	{
		built_err_msg(cmd->cmd[0], NULL, "minishell: exit: too many arguments");
		exit(1);
	}
	if (cmd->cmd[1])
	{
		exit_code = atoi_exit(cmd->cmd[1]);
		if (exit_code < 0 || exit_code > 255 )
		else
		{
			//error msg
			errno = 255;
			exit(255);
		}
	}
	exit (exit_code);
}
