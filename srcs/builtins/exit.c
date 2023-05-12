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

int	mini_exit(t_gen *gen, t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->cmd[1])
	{
		if (ft_isnumber(cmd->cmd[1]))
			exit_code = ft_atoi_mini(cmd->cmd[1]);
		else
		{
			//error msg
			errno = 255;
			exit(255);
		}
	}
	exit (exit_code);
}
