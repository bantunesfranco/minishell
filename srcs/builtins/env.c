/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 14:18:25 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/04 14:44:02 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_gen *gen, t_cmd *cmd)
{
	int	i;

	if (ft_arrlen(cmd->cmd) != 1)
		return (-1);
	i = 0;
	while (gen->env[i])
	{
		if (write(cmd->output->fd, gen->env[i], ft_strlen(gen->env[i])) == -1)
			return (-1);
		if (write(cmd->output->fd, "\n", 1) == -1)
			return (-1);
		i++;
	}
	return (0);
}
