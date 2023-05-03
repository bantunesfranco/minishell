/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 14:47:19 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/03 16:53:31 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_gen *gen, t_cmd *cmd)
{
	char	*path;
	char	*pwd;
	int		fd;
	int		len;

	fd = cmd->output->fd;
	path = getcwd(NULL, 0);
	if (!path)
		ft_error("minishell: ", errno);
	len = ft_strlen(path);
	pwd = (char *)malloc(len + 2);
	if (!pwd)
		ft_error("minishell: ", errno);
	ft_memmove(pwd, path, len);
	pwd[len] = '\n';
	pwd[len + 1] = '\0';
	if (write(fd, pwd, len + 2) == -1)
		ft_error("minishell: ", errno);
	free(path);
	free(pwd);
	return (0);
}
