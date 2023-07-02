/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 16:21:10 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/02 10:21:29 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static void	exit_error(char *msg, char *msg2, char *msg3)
{
	write(2, "minishell: ", 11);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
	}
	if (msg2)
	{
		write(2, msg2, ft_strlen(msg2));
		write(2, ": ", 2);
	}
	if (msg3)
		write(2, msg3, ft_strlen(msg3));
}

static int	atoi_exit(char *str)
{
	unsigned char	nb;
	int				i;
	long long		nb2;

	i = 0;
	nb = 0;
	nb2 = 0;
	if (!str || !ft_strlen(str))
		return (-1);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		nb2 = nb2 * 10 + (str[i] - '0');
		if (nb2 * -1 < LONG_MIN || nb2 > LONG_MAX)
			return (-1);
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-1);
	if (str[0] == '-')
		return (256 - nb);
	return ((int)nb);
}

int	mini_exit(t_gen *gen, t_cmd *cmd)
{
	int	exit_code;

	exit_code = gen->status;
	if (cmd->next == NULL && cmd->prev == NULL)
		if (write(2, "exit\n", 5) == -1)
			return (err_msg(cmd->cmd[0], "write error"), 1);
	if (cmd->cmd[1])
	{
		exit_code = atoi_exit(cmd->cmd[1]);
		if (exit_code == -1)
		{
			exit_error(cmd->cmd[0], cmd->cmd[1], "numeric argument required\n");
			// built_err_msg(cmd->cmd[0], NULL, "numeric argument required\n");
			exit(255);
		}
		if (ft_arrlen(cmd->cmd) > 2)
		{
			exit_error(cmd->cmd[0], NULL, "too many arguments\n");
			// built_err_msg(cmd->cmd[0], NULL, "too many arguments\n");
			return (1);
		}
	}
	set_echoctl();
	exit(exit_code);
}
