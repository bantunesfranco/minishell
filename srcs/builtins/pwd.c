/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 14:47:19 by bfranco       #+#    #+#                 */
/*   Updated: 2023/04/20 13:47:04 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **env, t_cmd *cmd)
{
	char	*path;
	int		fd;

	fd = cmd->output->fd;
	path = getcwd(NULL, 0);
	if (!path)
		ft_error("minishell: ", errno);
	if (write(fd, path, ft_strlen(path)) == -1)
		ft_error("minishell: ", errno);
	if (write(fd, "\n", 1) == -1)
		ft_error("minishell: ", errno);
	free(path);
	exit(0);
}
