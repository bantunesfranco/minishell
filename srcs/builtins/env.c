/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 14:18:25 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/03 12:25:32 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_gen *gen, t_cmd *cmd)
{
	int	i;

	if (ft_arrlen(cmd->cmd) != 1)
		return (built_err_msg(cmd->cmd[0], NULL, "too many arguments\n"), 1);
	i = 0;
	while (gen->env[i])
	{
		if (write(cmd->output->fd, gen->env[i], ft_strlen(gen->env[i])) == -1)
			return (err_msg(cmd->cmd[0], "write error"), 1);
		if (write(cmd->output->fd, "\n", 1) == -1)
			return (err_msg(cmd->cmd[0], "write error"), 1);
		i++;
	}
	return (0);
}
