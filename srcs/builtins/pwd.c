/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 14:47:19 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/06 14:10:22 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_gen *gen, t_cmd *cmd)
{
	char	*path;
	char	*pwd;
	int		fd;
	int		len;

	(void)gen;
	fd = cmd->output->fd;
	path = getcwd(NULL, 0);
	if (!path)
		return (err_msg(NULL, cmd->cmd[0]), 1);
	len = ft_strlen(path);
	pwd = (char *)malloc(len + 2);
	if (!pwd)
		return (err_msg(NULL, cmd->cmd[0]), 1);
	ft_memmove(pwd, path, len);
	pwd[len] = '\n';
	pwd[len + 1] = '\0';
	if (write(fd, pwd, len + 1) == -1)
		return (err_msg(cmd->cmd[0], "write error"), 1);
	free(path);
	free(pwd);
	return (0);
}
