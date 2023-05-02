/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 14:47:19 by bfranco       #+#    #+#                 */
/*   Updated: 2023/04/24 12:00:12 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **env, t_cmd *cmd)
{
	char	*path;
	int		fd;

	if (ft_arrlen(cmd->cmd) != 1)
		return (-1);
	fd = cmd->output->fd;
	path = getcwd(NULL, 0);
	if (!path)
		ft_error("minishell: ", errno);
	if (write(fd, path, ft_strlen(path)) == -1)
		ft_error("minishell: ", errno);
	if (write(fd, "\n", 1) == -1)
		ft_error("minishell: ", errno);
	free(path);
	return (0);
}
